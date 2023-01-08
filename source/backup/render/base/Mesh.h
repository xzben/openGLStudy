#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class Mesh : public Object, public NonCopyable
{
protected:
	GL_HANDLE m_vao;   //顶点数组对象
	GL_HANDLE m_vbo;  // 顶点buffer 对象
	GL_HANDLE m_ebo;  // 顶点索引 对象
	bool m_setuped;

	int   m_verticesCount; //顶点数量
	int   m_indicesCount; //索引数量
protected:
	virtual void setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount, VerticleMember vmembers);
public:
	Mesh();

	//禁止拷贝对象
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;

	virtual void setup(float* vertices, int verticlesCount, uint* indices, int indicesCount, VerticleMember vmembers = VerticleMember::POS_COLOR_TEXCOORD);
	virtual ~Mesh();

	virtual void draw();
};

END_NAMESPACE

#endif // !__2022_03_09_MESH_H__
