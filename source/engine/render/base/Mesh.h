#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"

class Mesh
{
protected:
	GL_HANDLE m_vao;   //顶点数组对象
	GL_HANDLE m_vbo;  // 顶点buffer 对象
	GL_HANDLE m_ebo;  // 顶点索引 对象
	bool m_setuped;

	int   m_verticesCount; //顶点数量
	int   m_indicesCount; //索引数量
protected:
	void setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount);
public:
	Mesh();

	virtual void setup(float* vertices, int verticlesCount, uint* indices, int indicesCount);
	virtual ~Mesh();

	virtual void draw();
};
#endif // !__2022_03_09_MESH_H__
