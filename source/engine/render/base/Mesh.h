#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"

class Mesh
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

	virtual void setup(float* vertices, int verticlesCount, uint* indices, int indicesCount);
	virtual ~Mesh();

	virtual void draw();
};
#endif // !__2022_03_09_MESH_H__
