#ifndef __2022_03_09_MESH_H__
#define __2022_03_09_MESH_H__
#include "common.h"

class Shader;
class Texture;

struct SubTexture
{
	std::string name;
	Texture* tex;
};

class Mesh
{
protected:
	GL_HANDLE m_vao;   //�����������
	GL_HANDLE m_vbo;  // ����buffer ����
	GL_HANDLE m_ebo;  // �������� ����
	bool m_setuped;
public:
	// ��������������Ϊ
	//---  x, y, z, r, g, b, tx, ty 
	float* vertices; //��������ָ��
	uint* indices; //������������
	int   verticesCount; //��������
	int   indicesCount; //��������

public:
	Mesh();

	virtual void setup();
	virtual ~Mesh();

	virtual void draw(Shader* shader = nullptr, Texture* tex = nullptr, SubTexture* texs = nullptr, int subTextCount = 0);
};
#endif // !__2022_03_09_MESH_H__
