#include "Vectex.h"

BEGIN_OGS_NAMESPACE

struct VertexMemberInfo
{
	VertexFmt member;
	int totalsize;
	uint32 itemtype;
	uint32 itemcount;
	const char* name;
};

const std::vector<VertexMemberInfo> VertexMemberInfos = {
	{ VertexFmt::POS,		sizeof(float) * 3, GL_FLOAT, 3,"aPos" },
	{ VertexFmt::COLOR,		sizeof(float) * 3, GL_FLOAT, 3,"aColor" },
	{ VertexFmt::TEXCOORD,	sizeof(float) * 2, GL_FLOAT, 2,"aTexCoord" },
	{ VertexFmt::NORMAL,	sizeof(float) * 3, GL_FLOAT, 3,"aNormal" },
	{ VertexFmt::TANGENT,	sizeof(float) * 3, GL_FLOAT, 3,"aTangent" },
	{ VertexFmt::BITANGENT, sizeof(float) * 3, GL_FLOAT, 3,"aBiTangent" },
};

inline int getVertexItemSize(uint32 fmt)
{
	int size = 0;
	for (auto it = VertexMemberInfos.begin(); it != VertexMemberInfos.end(); it++)
	{
		if (fmt <= 0) break;

		const VertexMemberInfo& info = *it;
		if (fmt & (uint32)(info.member))
		{
			size += info.totalsize;
			fmt = fmt & ~((uint32)info.member);
		}
	}

	return size;
}

Vectex::Vectex(VertexFmt fmt, int count, void* data /* = nullptr */)
{
	m_fmt = fmt;
	int cellsize = getVertexItemSize((uint32)fmt);
	m_size = cellsize * count;
	m_offset = cellsize;
	m_count = count;
	m_selfData = data == nullptr;
	m_data = data == nullptr ? new byte[m_size] : data;
}

Vectex::~Vectex()
{
	if (m_selfData && m_data)
	{
		delete m_data;
	}
	m_data = nullptr;
}

void Vectex::bindVBO(RenderHandle handle)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_STATIC_DRAW);

	int index = 0;
	int offset = 0;
	uint32 fmt = (uint32)m_fmt;
	for (auto it = VertexMemberInfos.begin(); it != VertexMemberInfos.end(); it++)
	{
		if (fmt <= 0) break;

		const VertexMemberInfo& info = *it;
		if (fmt & (uint32)(info.member))
		{
			glVertexAttribPointer(index, info.itemcount, info.itemtype, GL_FALSE, m_offset, (void*)offset);
			glEnableVertexAttribArray(index);
			fmt = fmt & ~((uint32)info.member);
			offset += info.totalsize;
		}
		index++;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Indices::Indices(int count, void* data /*= nullptr*/)
{
	m_count = count;
	int size = count * sizeof(uint32);
	m_selfData = data == nullptr;
	m_data = data == nullptr ? new byte[size] : data;
}

Indices::~Indices()
{
	if(m_selfData)
		delete m_data;
	m_data = nullptr;
}

void Indices::bindEBO(RenderHandle handle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32), m_data, GL_STATIC_DRAW);
}

END_OGS_NAMESPACE