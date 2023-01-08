#pragma once

#include "gfx/base/InputAssembler.h"
#include "gfx/opengl3/gl3_define.h"

BEGIN_OGS_GFX_NAMESPACE

class GL3InputAssembler : public InputAssembler
{
	DECLARE_RUNTIME_CLASS(GL3InputAssembler)
public:
	GL3InputAssembler();
	virtual ~GL3InputAssembler();

	virtual void active()override;
	virtual void deactive()override;
	virtual bool initialize(const InputAssemblerInfo& info);

protected:
	OGL_HANDLE m_handle;
};
END_OGS_GFX_NAMESPACE