#pragma once

#include "pipeline/pipeline_define.h"
#include "pipeline/RenderFlow.h"
BEGIN_OGS_PIPLINE_NAMESPACE

class ForwardFlow : public RenderFlow
{
	DECLARE_RUNTIME_CLASS(ForwardFlow)
public:
	virtual bool initialize();
	virtual bool active();
	virtual void destroy();

	virtual void render(Camera* camera);

};
END_OGS_PIPLINE_NAMESPACE