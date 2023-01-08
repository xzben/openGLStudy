#pragma once

#include "define.h"
#include "core/render/render_macro.h"

BEGIN_OGS_NAMESPACE
class Vectex : public Object
{
public:
	Vectex(VertexFmt fmt, int count, void* data = nullptr);
	~Vectex();

	void bindVBO(RenderHandle handle);
	int getCount() { return m_count; }
private:
	VertexFmt m_fmt;
	bool  m_selfData;
	void* m_data; //数据
	int   m_size; //所有数据size
	int   m_offset; //一个元素顶点的size
	int   m_count; //顶点数量
};

class Indices : public Object
{
public:
	Indices(int count, void* data = nullptr);
	~Indices();

	void bindEBO(RenderHandle handle);
	int getCount() { return m_count; }
private:
	int m_count; //索引数量
	bool m_selfData;
	void* m_data;
};
END_OGS_NAMESPACE