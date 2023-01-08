#include "GL3InputAssembler.h"
#include "glad/glad.h"
#include "gfx/base/Buffer.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3InputAssembler)

GL3InputAssembler::GL3InputAssembler()
{
	glGenVertexArrays(1, &m_handle);
}

GL3InputAssembler::~GL3InputAssembler()
{
	glDeleteVertexArrays(1, &m_handle);
}

static uint32 getGLFormat(FormatType type)
{
	uint32 format = GL_FLOAT;
	switch (type)
	{
	case OGS::Gfx::FormatType::UNORM:
		format = GL_UNSIGNED_BYTE;
		break;
	case OGS::Gfx::FormatType::SNORM:
		format = GL_BYTE;
		break;
	case OGS::Gfx::FormatType::UINT:
		format = GL_UNSIGNED_INT;
		break;
	case OGS::Gfx::FormatType::INT:
		format = GL_INT;
		break;
	case OGS::Gfx::FormatType::UFLOAT:
		format = GL_FLOAT;
		break;
	case OGS::Gfx::FormatType::FLOAT:
		format = GL_FLOAT;
		break;
	}

	return format;
}
bool GL3InputAssembler::initialize(const InputAssemblerInfo& info)
{
	m_attributes = info.attributes;
	m_vertexBuffers = info.vertexBuffers;
	m_indexBuffer = info.indexBuffer;
	m_indirectBuffer = info.indirectBuffer;
	glBindVertexArray(m_handle);
	int offset = 0;
	Buffer* vertexBuff = m_vertexBuffers[0].get();
	
	int stride = vertexBuff->getStride();
	vertexBuff->active();
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
	{
		const FormatInfo& info = getFormatInfo(it->format);
		glVertexAttribPointer(it->location, info.count, getGLFormat(info.type), it->isNormalized ? GL_TRUE : GL_FALSE, stride, (void*)offset);
	}
	vertexBuff->deactive();
	glBindVertexArray(0);

	return true;
}

void GL3InputAssembler::active()
{
	glBindVertexArray(m_handle);
}

void GL3InputAssembler::deactive()
{
	glBindVertexArray(0);
}
END_OGS_GFX_NAMESPACE