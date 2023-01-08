#pragma once

#include "pipeline_define.h"

namespace OGS
{
	class Camera;
}

BEGIN_OGS_PIPLINE_NAMESPACE

class RenderPipeline;
class RenderFlow;

class RenderStage : public Object
{
public:
	RenderStage();
	virtual ~RenderStage();
	bool initialize();
	void active(RenderPipeline* pipeline, RenderFlow* flow);
	void render(OGS::Camera* camera);
protected:
	std::string m_name;
	int			m_priority;
	int			m_tag;
	bool		m_enable;
	WeakRef<RenderPipeline> m_pipeline;
	WeakRef<RenderFlow>		m_flow;
};
END_OGS_PIPLINE_NAMESPACE