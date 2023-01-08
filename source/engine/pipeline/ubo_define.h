#pragma once

#include "define.h"
#include "gfx/base/Uniform.h"
#include "gfx/base/DescriptorSetLayoutBinding.h"

BEGIN_OGS_PIPLINE_NAMESPACE

enum PipelineGlobalBindings {
	UBO_GLOBAL,
	UBO_CAMERA,
	UBO_SHADOW,
	UBO_CSM, // should reserve slot for this optional ubo

	SAMPLER_SHADOWMAP,
	SAMPLER_ENVIRONMENT, // don't put this as the first sampler binding due to Mac GL driver issues: cubemap at texture unit 0 causes rendering issues
	SAMPLER_SPOT_SHADOW_MAP,
	SAMPLER_DIFFUSEMAP,

	COUNT,
};

class UBOGlobal
{
public:
	static const uint16 TIME_OFFSET;
	static const uint16 SCREEN_SIZE_OFFSET;
	static const uint16 NATIVE_SIZE_OFFSET;
	static const uint16 DEBUG_VIEW_MODE_OFFSET;
	static const uint16 DEBUG_VIEW_COMPOSITE_PACK_1_OFFSET;
	static const uint16 DEBUG_VIEW_COMPOSITE_PACK_2_OFFSET;
	static const uint16 DEBUG_VIEW_COMPOSITE_PACK_3_OFFSET;
	static const uint16 COUNT;
	static const uint16 SIZE;
	static const std::string NAME;
	static const uint16 BINDING;
	static const Gfx::DescriptorSetLayoutBinding DESCRIPTOR;
	static const Gfx::UniformBlock LAYOUT;
};

class UBOCamera
{
public:
	static const uint16 MAT_VIEW_OFFSET;
	static const uint16 MAT_VIEW_INV_OFFSET;
	static const uint16 MAT_PROJ_OFFSET;
	static const uint16 MAT_PROJ_INV_OFFSET;
	static const uint16 MAT_VIEW_PROJ_OFFSET;
	static const uint16 MAT_VIEW_PROJ_INV_OFFSET;
	static const uint16 CAMERA_POS_OFFSET;
	static const uint16 SURFACE_TRANSFORM_OFFSET;
	static const uint16 SCREEN_SCALE_OFFSET;
	static const uint16 EXPOSURE_OFFSET;
	static const uint16 MAIN_LIT_DIR_OFFSET;
	static const uint16 MAIN_LIT_COLOR_OFFSET;
	static const uint16 AMBIENT_SKY_OFFSET;
	static const uint16 AMBIENT_GROUND_OFFSET;
	static const uint16 GLOBAL_FOG_COLOR_OFFSET;
	static const uint16 GLOBAL_FOG_BASE_OFFSET;
	static const uint16 GLOBAL_FOG_ADD_OFFSET;
	static const uint16 NEAR_FAR_OFFSET;
	static const uint16 VIEW_PORT_OFFSET;
	static const uint16 COUNT;
	static const uint16 SIZE;

	static const std::string NAME;
	static const uint16 BINDING;
	static const Gfx::DescriptorSetLayoutBinding DESCRIPTOR;
	static const Gfx::UniformBlock LAYOUT;
};

END_OGS_PIPLINE_NAMESPACE