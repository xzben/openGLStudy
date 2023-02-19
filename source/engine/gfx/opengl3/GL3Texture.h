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
	uint32 getHandle() override { return m_handle; }
	void initialize(TextureInfo* info);
	void initialize(const std::string& filename);
	void resize(uint32 width, uint32 height) override;
protected:
	OGL_HANDLE m_handle;
};
END_OGS_GFX_NAMESPACE