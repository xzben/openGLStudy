#include "GL3Buffer.h"
#include "glad/glad.h"
#include "core/filesystem/Data.h"
BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3Buffer)

GL3Buffer::GL3Buffer()
{
	glGenBuffers(1, &m_handle);
}

GL3Buffer::~GL3Buffer()
{
	glDeleteBuffers(1, &m_handle);
	m_handle = 0;
}

static uint32 getGLUsage(BufferUsageBit m_usage)
{
	uint32 usage = GL_STATIC_DRAW;

	switch (m_usage)
	{
	case BufferUsageBit::TRANSFER_SRC:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	case BufferUsageBit::TRANSFER_DST:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	case BufferUsageBit::INDEX:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	case BufferUsageBit::VERTEX:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	case BufferUsageBit::UNIFORM:
	{
		usage = GL_DYNAMIC_DRAW;
		break;
	}
	case BufferUsageBit::STORAGE:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	case BufferUsageBit::INDIRECT:
	{
		usage = GL_STATIC_DRAW;
		break;
	}
	}

	return usage;
}
static uint32 getGLTarget(BufferUsageBit m_usage)
{
	uint32 target = 0;
	switch (m_usage)
	{
	case BufferUsageBit::TRANSFER_SRC:
	{
		target = GL_COPY_READ_BUFFER;
		break;
	}
	case BufferUsageBit::TRANSFER_DST:
	{
		target = GL_COPY_WRITE_BUFFER;
		break;
	}
	case BufferUsageBit::INDEX:
	{
		target = GL_ELEMENT_ARRAY_BUFFER;
		break;
	}
	case BufferUsageBit::VERTEX:
	{
		target = GL_ARRAY_BUFFER;
		break;
	}
	case BufferUsageBit::UNIFORM:
	{
		target = GL_UNIFORM_BUFFER;
		break;
	}
	case BufferUsageBit::STORAGE:
	{
		target = GL_TEXTURE_BUFFER;
		break;
	}
	case BufferUsageBit::INDIRECT:
	{
		target = GL_DRAW_INDIRECT_BUFFER;
		break;
	}
	}

	return target;
}
bool GL3Buffer::updateSubBuffer(void* data, uint32 offset, uint32 size)
{
	uint32 target = getGLTarget(m_usage);

	ASSERT(target != 0, "buffer usage is invalid");
	glBindBuffer(target, m_handle);
	glBufferSubData(target, offset, m_size, data);
	glBindBuffer(target, 0);

	return true;
}

bool GL3Buffer::updateBuffer(void* data, uint32 size)
{
	uint32 target = getGLTarget(m_usage);
	uint32 usage = getGLUsage(m_usage);
	
	ASSERT(target != 0, "buffer usage is invalid");
	glBindBuffer(target, m_handle);
	glBufferData(target, m_size, data, usage);
	glBindBuffer(target, 0);

	return true;
}

void  GL3Buffer::active()
{
	uint32 target = getGLTarget(m_usage);
	glBindBuffer(target, m_handle);
}

void  GL3Buffer::deactive()
{
	uint32 target = getGLTarget(m_usage);
	glBindBuffer(target, 0);
}
END_OGS_GFX_NAMESPACE