#pragma once


#include "gfx/base/Texture.h"
#include "gfx/opengl3/gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3Texture : public Texture
{
	DECLARE_RUNTIME_CLASS(GL3Texture)
public:
	GL3Texture();
	virtual ~GL3Texture();

	void initialize(TextureInfo* info);
protected:
	OGL_HANDLE m_handle;
};
END_OGS_GFX_NAMESPACE