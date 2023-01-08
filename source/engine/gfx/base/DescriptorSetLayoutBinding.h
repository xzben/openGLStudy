#pragma once

#include "common.h"
#include "gfx_base_define.h"
#include <vector>

BEGIN_OGS_GFX_NAMESPACE

class Sampler;
class DescriptorSetLayoutBinding
{
public:
	uint16 binding = -1;
	DescriptorType descriptorType{ DescriptorType::UNKNOWN };
	uint32 count = 0;
	ShaderStageFlagBit stageFlags{ ShaderStageFlagBit::NONE };
	std::vector<AutoRef<Sampler>> immutableSamplers;
};

END_OGS_GFX_NAMESPACE