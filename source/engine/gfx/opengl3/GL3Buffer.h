#pragma once

#include "gfx/base/Buffer.h"
#include "gl3_define.h"
BEGIN_OGS_GFX_NAMESPACE

class GL3Buffer : public Buffer
{
	DECLARE_RUNTIME_CLASS(GL3Buffer)
public:
	GL3Buffer();
	virtual ~GL3Buffer();
	virtual void active() override;
	virtual void deactive() override;
	virtual bool updateBuffer(void* data, uint32 size) override;
	virtual bool updateSubBuffer(void* data, uint32 offset, uint32 size)  override;
private:
	OGL_HANDLE m_handle;
};

END_OGS_GFX_NAMESPACE