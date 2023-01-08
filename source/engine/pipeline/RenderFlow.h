#pragma once

#include "pipeline_define.h"

namespace OGS
{
	class Camera;
}

BEGIN_OGS_PIPLINE_NAMESPACE

class RenderStage;
class RenderPipeline;

class RenderFlow : public Object
{
public:
	RenderFlow();
	virtual ~RenderFlow();

	bool initialize();
	void actvie(RenderPipeline* pipeline);
	void render(OGS::Camera* camera);
protected:
	std::string m_name;
	int			m_priority;
	int			m_tag;
	std::vector<AutoRef<RenderStage>> m_stages;
	WeakRef<RenderPipeline> m_pipeline;
};
END_OGS_PIPLINE_NAMESPACE