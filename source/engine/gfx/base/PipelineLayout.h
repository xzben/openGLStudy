#pragma once

#include "gfx_base_define.h"
#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class DescriptSetLayout;

class PipelineLayoutInfo
{
public:
	std::vector<AutoRef<DescriptSetLayout>> setLayouts;
};

class PipelineLayout : public GfxObject
{
	DECLARE_RUNTIME_CLASS(PipelineLayout)
public:
	PipelineLayout() :GfxObject(ObjectType::PIPELINE_LAYOUT) {}
protected:
	std::vector<AutoRef<DescriptSetLayout>> m_setLayouts;

};

END_OGS_GFX_NAMESPACE