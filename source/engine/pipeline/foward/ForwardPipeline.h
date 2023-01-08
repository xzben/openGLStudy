#pragma once

#include "pipeline/Pipeline.h"

BEGIN_OGS_PIPLINE_NAMESPACE

class ForwardPipeline : public RenderPipeline
{
public:
	ForwardPipeline();
	virtual ~ForwardPipeline();
	
	virtual bool initialize();
	virtual bool active();
	virtual void destroy();
};
END_OGS_PIPLINE_NAMESPACE