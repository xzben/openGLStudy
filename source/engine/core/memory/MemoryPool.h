#pragma once

#include "common.h"
#include <mutex>

BEGIN_OGS_NAMESPACE

enum MemSize
{
	SIZE1K = 1024,
	SIZE1M = 1024 * SIZE1K,
	SIZE1G = 1024 * SIZE1M,
};

//basic memory node structure
struct apr_memnode_t {
	uint32			magic;			//���ڱ������ڴ�����ڴ�������			    
	apr_memnode_t* next;			//ָ����һ���ڴ�ռ�ڵ�
	apr_memnode_t** ref;			//ָ��ǰ�ڴ�ռ�ڵ�
	uint32			index;			//��ǰ�ڴ�ռ�ڵ���ܹ��ڴ��С
	uint32			free_index;		//��ǰ�ڴ�ռ��еĿ��ÿռ�
	char* first_avail;	//ָ��ǰ���ÿռ����ʼ��ַ����	������
	char* endp;			//ָ��ǰ���õ�ַ�Ľ�����ַ��
};

class Allocator
{
public:
	enum {
		APR_ALLOCATOR_MAX_FREE_UNLIMITED = 0,
		DEFAULT_ALIGN = 8,
		MAX_INDEX = 20,
		BOUNDARY_INDEX = 4, //������������С�ķ��䵥Ԫ��Сʹ��ʱ���Ƕ� size >> BOUNDARY_INDEX ����������4K�Ĵ�С�����С�Ƿ������Ĵ�С������λ
		BOUNDARY_SIZE = (1 << BOUNDARY_INDEX), // 4 byte ����Ĵ�С��λ
		MIN_ALLOC = 2 * BOUNDARY_SIZE,  // ��Сalloc ��size 8 byte
	};
public:
	Allocator(size_t nMaxSize = APR_ALLOCATOR_MAX_FREE_UNLIMITED);
	virtual ~Allocator();
	inline const int GetMemNodeSize()
	{
		const int nMemNodeSize = Align(sizeof(apr_memnode_t), DEFAULT_ALIGN);
		return nMemNodeSize;
	}
	/*
	*	��õ�ǰ������������ڴ��ı��ֵ
	*/
	inline uint32 GetMagic()
	{
		return m_uiMagic;
	}
	/*
	*	��� nAllocSize �ռ��С�Ľڵ�
	*/
	apr_memnode_t* Alloc(size_t nAllocSize);
	/*
	*	�ͷ�node�ڵ�Ŀռ䣬ע��������ͷŲ�һ����ֱ�Ӹ�ϵͳ����
	*	��������ʱ���ڷ������У����´�Ҫ�õ��ڴ�ʹ��
	*/
	void Free(apr_memnode_t* node);
private:
	/*
	*	����һ���ϴ���������
	*/
	static inline uint32	CreateMagic()
	{
		double start = 1, end = RAND_MAX;
		double uiMagic = (start + (end - start) * rand() / (RAND_MAX + 1.0));
		uiMagic *= uiMagic;
		return (uint32)uiMagic;
	}
	/*
	*	function:	������ӽ�nSize �� nBoundary ������������������ð�ָ���ֽڶ����Ĵ�С
	*	parameter:	nSize Ϊ������ nBoundary������Ϊ 2 �ı���
	*	example:	Align(7�� 4) = 8��Align(21, 16) = 32
	*/
	static inline size_t Align(size_t nSize, size_t nBoundary)
	{
		return ((nSize + nBoundary - 1) & ~(nBoundary - 1));
	}
	/*
	*	function:	���÷����ӵ�����ڴ����ռ����ƣ������ù�ϵ����
	*				�����������ж���ڴ�ʱ�Ὣ�ڴ淵�ظ�ϵͳ����
	*	paramter:	allocator : Ҫ���õķ����ӣ� nSize�� Ҫ���õĴ�С
	*
	*/
	void inline SetMaxSize(size_t nSize)
	{
		//���㰴 4K ����Ŀռ��С�󣬻�����С��4K����ֵ
		uint32 uiMaxIndex = Align(nSize, BOUNDARY_SIZE) >> BOUNDARY_INDEX;

		//�����µ����ɴ�ſռ��С�������Ҫ��֤��ǰ m_uiCurAllocIndex(��ǰ�ɴ洢�ڷ������е��ڴ��С)
		//������ĵ�����������������ֵʱ��m_uiCurAllocIndex ==  m_uiMaxIndex ��Ҫ����Ӧ�����ӣ�
		//��� m_uiCurAllocIndex < m_uiMaxIndex ��ô���������ֵҲ����Ӱ�죬��Ϊ m_uiCurAllocIndex ���ں�����ʹ����
		//�ﵽ���ֵ��
		m_uiCurAllocIndex += uiMaxIndex - m_uiMaxIndex;
		m_uiMaxIndex = uiMaxIndex;

		if (m_uiCurAllocIndex > uiMaxIndex)
			m_uiCurAllocIndex = uiMaxIndex;
	}
	/*
	*	���������й��صĿռ�ȫ����ϵͳ����
	*/
	void Destroy();
private:
	uint32			m_uiMagic; //���ڼ�¼�η�����������ڴ��ı��ֵ
	uint32			m_uiCurMaxBlockIndex; //�������е�ǰ���õ�����ĵĴ�Сindex
	uint32			m_uiMaxIndex;//���������Դ洢�����ռ��Сindex
	uint32			m_uiCurAllocIndex;//��ǰ�Ѿ�����Ŀ����ڷ������еĿռ��С����ֵ������ m_uiMaxIndex��Χ��
	std::mutex		m_mutex;		 //���̷߳�����
	apr_memnode_t* m_pfree[MAX_INDEX];//��������ǰ���صĿ����ڴ��
};

class MemoryPool
{
public:
	MemoryPool(size_t nMaxSize = 0);
	virtual ~MemoryPool();
	static MemoryPool* getInstance()
	{
		static MemoryPool Instance;
		return &Instance;
	}
	virtual void* Alloc(size_t nAllocaSize);
	virtual bool Free(void* pMem);
private:
	Allocator* m_pAllocator;
};


class AllocFromMemoryPool
{
public:
	inline void* operator new(size_t size)
	{
		return MemoryPool::getInstance()->Alloc(size);
	}
	inline void* operator new[](size_t size)
	{
		return MemoryPool::getInstance()->Alloc(size);
	}
		inline void	operator delete(void* pobj)
	{
		MemoryPool::getInstance()->Free(pobj);
	}
	inline void	operator delete[](void* pobj)
	{
		MemoryPool::getInstance()->Free(pobj);
	}
		virtual ~AllocFromMemoryPool()
	{

	}
protected:  //�����캯������Ϊ�������ͣ�ʹ���಻�ܱ�ֱ����������ֻ�ܱ��̳�ʹ��
	AllocFromMemoryPool()
	{

	}
};

END_OGS_NAMESPACE