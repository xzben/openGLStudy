#pragma once

#include "pipeline/pipeline_define.h"
#include "pipeline/RenderFlow.h"

namespace OGS
{
	class Camera;
}

BEGIN_OGS_PIPLINE_NAMESPACE

class ShadowFlow : public RenderFlow
{
	DECLARE_RUNTIME_CLASS(ShadowFlow)
public:
	virtual bool initialize();
	virtual bool active();
	virtual void destroy();

	virtual void render(Camera* camera);
};
END_OGS_PIPLINE_NAMESPACE