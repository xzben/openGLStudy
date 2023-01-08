#pragma once

#include "gfx_base_define.h"
#include "GfxObject.h"
#include "DescriptorSetLayoutBinding.h"

BEGIN_OGS_GFX_NAMESPACE

class DescriptorSetLayoutInfo
{
public:
	std::vector<DescriptorSetLayoutBinding> bindings;
};

class DescriptorSetLayout : public GfxObject
{
	DECLARE_RUNTIME_CLASS(DescriptorSetLayout)
public:
	DescriptorSetLayout() :GfxObject(ObjectType::DESCRIPTOR_SET_LAYOUT) {};
protected:
	std::vector<DescriptorSetLayoutBinding> m_bindings;
	std::vector<int32>						m_binddingIndices;
	std::vector<int32>						m_descriptorIndices;
};
END_OGS_GFX_NAMESPACE