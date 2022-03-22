#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"
#include "base/Object.h"

BEGIN_NAMESPACE

class Mesh : public Object
{
protected:
	GL_HANDLE m_vao;   //�����������
	GL_HANDLE m_vbo;  // ����buffer ����
	GL_HANDLE m_ebo;  // �������� ����
	bool m_setuped;

	int   m_verticesCount; //��������
	int   m_indicesCount; //��������
protected:
	void setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount);
public:
	Mesh();

	//��ֹ��������
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;

	virtual void setup(float* vertices, int verticlesCount, uint* indices, int indicesCount);
	virtual ~Mesh();

	virtual void draw();
};

END_NAMESPACE

#endif // !__2022_03_09_MESH_H__
