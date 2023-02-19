#pragma once

#include "gfx/base/Shader.h"
#include "gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3Shader : public Shader
{
	DECLARE_RUNTIME_CLASS(GL3Shader)
public:
	GL3Shader();
	virtual ~GL3Shader();
	virtual bool initilize(ShaderInfo* info) override;

protected:
	OGL_HANDLE m_handle;
};
END_OGS_GFX_NAMESPACE