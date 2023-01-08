#include "GL3Shader.h"
#include "glad/glad.h"

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GL3Shader)

GL3Shader::GL3Shader()
{
	m_handle = glCreateProgram();
}

GL3Shader::~GL3Shader()
{
	glDeleteProgram(m_handle);
}


END_OGS_GFX_NAMESPACE