#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class Mesh : public Object, public NonCopyable
{
protected:
	GL_HANDLE m_vao;   //�����������
	GL_HANDLE m_vbo;  // ����buffer ����
	GL_HANDLE m_ebo;  // �������� ����
	bool m_setuped;

	int   m_verticesCount; //��������
	int   m_indicesCount; //��������
protected:
	virtual void setupGLData(float* vertices, int verticlesCount, uint* indices, int indicesCount, VerticleMember vmembers);
public:
	Mesh();

	//��ֹ��������
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
