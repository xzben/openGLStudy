#include "MemoryPool.h"


BEGIN_OGS_NAMESPACE

/////////////////////////////////////////////////////////////////////////////////////////
//class Allocator public
Allocator::Allocator(size_t nMaxSize /*= APR_ALLOCATOR_MAX_FREE_UNLIMITED*/)
{
	m_uiMagic = CreateMagic();
	m_uiCurMaxBlockIndex = 0; //��ʼ״̬�£�m_pfree[] Ϊ�գ�����û�������ÿ� 
	m_uiMaxIndex = APR_ALLOCATOR_MAX_FREE_UNLIMITED;//��ʼ״̬Ϊ�ɴ洢�ռ�����
	m_uiCurAllocIndex = 0;//��ǰ�Ѿ�����Ŀ����ڷ������еĿռ��С����ֵ������ m_uiMaxIndex��Χ��
	memset(m_pfree, 0, sizeof(m_pfree));

	if (nMaxSize != APR_ALLOCATOR_MAX_FREE_UNLIMITED)
		SetMaxSize(nMaxSize);
}
Allocator::~Allocator()
{
	Destroy();
}
apr_memnode_t* Allocator::Alloc(size_t nAllocSize)
{
	apr_memnode_t* node, ** ref;
	uint32 uiCurMaxBlockIndex;
	size_t nSize, i, index;

	const int nMemNodeSize = GetMemNodeSize();

	nSize = Align(nAllocSize + nMemNodeSize, BOUNDARY_SIZE);
	if (nSize < nAllocSize) //��������nAllocSize�����¼����nSize��nAllocSizeС
	{
		return NULL;
	}
	if (nSize < MIN_ALLOC)
		nSize = MIN_ALLOC;

	//ת����СֵΪ ��4KΪ��λ��ֵ��������free������Ӧ��index
	//����nSize ��СΪ8K��������������index ��С = 1
	index = (nSize >> BOUNDARY_INDEX) - 1;
	if (index > UINT32_MAX) //����Ŀռ�����򲻷���
	{
		return NULL;
	}
	if (index <= m_uiCurMaxBlockIndex)//��ǰ���ڿ��õ��ڴ�鹻index
	{
		m_mutex.lock();

		uiCurMaxBlockIndex = m_uiCurMaxBlockIndex;
		ref = &m_pfree[index];
		i = index;
		while (NULL == *ref && i < uiCurMaxBlockIndex)
			ref++, i++;

		if (NULL != (node = *ref))
		{
			if (NULL == (*ref = node->next) && i >= uiCurMaxBlockIndex)
				//����ҵ��Ŀ����ڴ���ǵ�ǰ�����������Ŀ飬�������һ������
				//����·������е�ǰ�Ŀ�������
			{
				do {
					ref--;
					uiCurMaxBlockIndex--;
				} while (NULL == *ref && uiCurMaxBlockIndex > 0);
				m_uiCurMaxBlockIndex = uiCurMaxBlockIndex;
			}

			m_uiCurAllocIndex += node->index + 1;
			if (m_uiCurAllocIndex > m_uiMaxIndex)
				m_uiCurAllocIndex = m_uiMaxIndex;

			m_mutex.unlock();
			node->next = NULL;
			node->first_avail = (char*)node + nMemNodeSize;
			return node;
		}
		m_mutex.unlock();
	}
	else if (m_pfree[0])
	{
		m_mutex.lock();
		ref = &m_pfree[0];
		while (NULL != (node = *ref) && index > node->index)
			ref = &node->next;

		if (node)
		{
			*ref = node->next;
			m_uiCurAllocIndex += node->index + 1;
			if (m_uiCurAllocIndex > m_uiMaxIndex)
				m_uiCurAllocIndex = m_uiMaxIndex;

			m_mutex.unlock();
			node->next = NULL;
			node->first_avail = (char*)node + nMemNodeSize;
			return node;
		}
		m_mutex.unlock();
	}
	if (NULL == (node = (apr_memnode_t*)malloc(nSize)))
	{
		return NULL;
	}
	node->magic = m_uiMagic;
	node->next = NULL;
	node->index = index;
	node->first_avail = (char*)node + nMemNodeSize;
	node->endp = (char*)node + nSize;

	return node;
}
void Allocator::Free(apr_memnode_t* node)
{
	apr_memnode_t* next, * freelist = NULL;
	uint32 index, uiCurMaxBlockIndex;
	uint32 uiMaxIndex, uiCurAllocIndex;

	m_mutex.lock();
	uiCurMaxBlockIndex = m_uiCurMaxBlockIndex;
	uiMaxIndex = m_uiMaxIndex;
	uiCurAllocIndex = m_uiCurAllocIndex;

	do {
		next = node->next;
		index = node->index;

		if (APR_ALLOCATOR_MAX_FREE_UNLIMITED != uiMaxIndex
			&& index + 1 > uiCurAllocIndex) //�����ǰindex + 1 �ռ��ǳ����޶�maxindex �Ŀռ�����ɾ��
		{
			node->next = freelist;
			freelist = node;
		}
		else if (index < MAX_INDEX)
		{
			if (NULL == (node->next = m_pfree[index])
				&& index > uiCurMaxBlockIndex)
			{
				uiCurMaxBlockIndex = index;
			}
			m_pfree[index] = node;
			if (uiCurAllocIndex >= index + 1)
				uiCurAllocIndex -= index + 1;
			else
				uiCurAllocIndex = 0;
		}
		else
		{
			node->next = m_pfree[0];
			m_pfree[0] = node;
			if (uiCurAllocIndex >= index + 1)
				uiCurAllocIndex -= index + 1;
			else
				uiCurAllocIndex = 0;

		}
	} while (NULL != (node = next));
	m_uiCurMaxBlockIndex = uiCurMaxBlockIndex;
	m_uiCurAllocIndex = uiCurAllocIndex;

	m_mutex.unlock();
	while (NULL != freelist)
	{
		node = freelist;
		freelist = node->next;
		free(node);
	}
}
void Allocator::Destroy()
{
	uint32 index;
	apr_memnode_t* node, ** ref;

	for (index = 0; index < MAX_INDEX; index++)
	{
		ref = &m_pfree[index];
		while ((node = *ref) != NULL) {
			*ref = node->next;
			free(node);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
//class MemoryPool public
MemoryPool::MemoryPool(size_t nMaxSize /*= Allocator::APR_ALLOCATOR_MAX_FREE_UNLIMITED*/)
{
	m_pAllocator = new Allocator(nMaxSize);
}
void* MemoryPool::Alloc(size_t nAllocaSize)
{
	apr_memnode_t* node = m_pAllocator->Alloc(nAllocaSize);
	if (node == NULL)
	{
		return NULL;
	}
	return node->first_avail;
}
bool MemoryPool::Free(void* pMem)
{
	if (NULL == pMem)
	{
		return false;
	}
	apr_memnode_t* node = (apr_memnode_t*)((char*)pMem - m_pAllocator->GetMemNodeSize());
	if (node->magic != m_pAllocator->GetMagic()) //����˶��ڴ治�Ǵ��ڴ�صķ����������
	{
		return false;
	}
	m_pAllocator->Free(node);
	return true;
}

MemoryPool::~MemoryPool()
{
	if (m_pAllocator)
		delete m_pAllocator;
}

END_OGS_NAMESPACE