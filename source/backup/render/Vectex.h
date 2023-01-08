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
	void* m_data; //����
	int   m_size; //��������size
	int   m_offset; //һ��Ԫ�ض����size
	int   m_count; //��������
};

class Indices : public Object
{
public:
	Indices(int count, void* data = nullptr);
	~Indices();

	void bindEBO(RenderHandle handle);
	int getCount() { return m_count; }
private:
	int m_count; //��������
	bool m_selfData;
	void* m_data;
};
END_OGS_NAMESPACE