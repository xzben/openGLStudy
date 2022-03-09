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
	GL_HANDLE m_vao;   //顶点数组对象
	GL_HANDLE m_vbo;  // 顶点buffer 对象
	GL_HANDLE m_ebo;  // 顶点索引 对象
	bool m_setuped;
public:
	// 顶点数组中数据为
	//---  x, y, z, r, g, b, tx, ty 
	float* vertices; //顶点数组指针
	uint* indices; //顶点索引数据
	int   verticesCount; //顶点数量
	int   indicesCount; //索引数量

public:
	Mesh();

	virtual void setup();
	virtual ~Mesh();

	virtual void draw(Shader* shader = nullptr, Texture* tex = nullptr, SubTexture* texs = nullptr, int subTextCount = 0);
};
#endif // !__2022_03_09_MESH_H__
