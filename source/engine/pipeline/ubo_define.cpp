#include "ubo_define.h"
#include "pipeline_define.h"
#include "gfx/base/gfx_base_define.h"

BEGIN_OGS_PIPLINE_NAMESPACE

const uint16 UBOGlobal::TIME_OFFSET = 0;
const uint16 UBOGlobal::SCREEN_SIZE_OFFSET = UBOGlobal::TIME_OFFSET + 4;
const uint16 UBOGlobal::NATIVE_SIZE_OFFSET = UBOGlobal::SCREEN_SIZE_OFFSET + 4;
const uint16 UBOGlobal::DEBUG_VIEW_MODE_OFFSET = UBOGlobal::NATIVE_SIZE_OFFSET + 4;
const uint16 UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_1_OFFSET = UBOGlobal::DEBUG_VIEW_MODE_OFFSET + 4;
const uint16 UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_2_OFFSET = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_1_OFFSET + 4;
const uint16 UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_3_OFFSET = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_2_OFFSET + 4;
const uint16 UBOGlobal::COUNT = UBOGlobal::DEBUG_VIEW_COMPOSITE_PACK_3_OFFSET + 4;
const uint16 UBOGlobal::SIZE = UBOGlobal::COUNT * 4;

const std::string UBOGlobal::NAME = "CCGlobal";
const uint16 UBOGlobal::BINDING = PipelineGlobalBindings::UBO_GLOBAL;
const Gfx::DescriptorSetLayoutBinding UBOGlobal::DESCRIPTOR = {
	UBOGlobal::BINDING, Gfx::DescriptorType::UNIFORM_BUFFER, 1, Gfx::ShaderStageFlagBit::ALL,
};

const Gfx::UniformBlock UBOGlobal::LAYOUT{ 
	SetIndex::GLOBAL, UBOGlobal::BINDING, UBOGlobal::NAME, 1, {
			{"cc_time", Gfx::Type::FLOAT4, 1},
			{"cc_screenSize", Gfx::Type::FLOAT4, 1},
			{"cc_nativeSize", Gfx::Type::FLOAT4, 1},

			{"cc_debug_view_mode", Gfx::Type::FLOAT, 4},
			{"cc_debug_view_composite_pack_1", Gfx::Type::FLOAT, 4},
			{"cc_debug_view_composite_pack_2", Gfx::Type::FLOAT, 4},
			{"cc_debug_view_composite_pack_3", Gfx::Type::FLOAT, 4},
		}
	};


const uint16 UBOCamera::MAT_VIEW_OFFSET = 0;
const uint16 UBOCamera::MAT_VIEW_INV_OFFSET = UBOCamera::MAT_VIEW_OFFSET + 16;
const uint16 UBOCamera::MAT_PROJ_OFFSET = UBOCamera::MAT_VIEW_INV_OFFSET + 16;
const uint16 UBOCamera::MAT_PROJ_INV_OFFSET = UBOCamera::MAT_PROJ_OFFSET + 16;
const uint16 UBOCamera::MAT_VIEW_PROJ_OFFSET = UBOCamera::MAT_PROJ_INV_OFFSET + 16;
const uint16 UBOCamera::MAT_VIEW_PROJ_INV_OFFSET = UBOCamera::MAT_VIEW_PROJ_OFFSET + 16;
const uint16 UBOCamera::CAMERA_POS_OFFSET = UBOCamera::MAT_VIEW_PROJ_INV_OFFSET + 16;
const uint16 UBOCamera::SURFACE_TRANSFORM_OFFSET = UBOCamera::CAMERA_POS_OFFSET + 4;
const uint16 UBOCamera::SCREEN_SCALE_OFFSET = UBOCamera::SURFACE_TRANSFORM_OFFSET + 4;
const uint16 UBOCamera::EXPOSURE_OFFSET = UBOCamera::SCREEN_SCALE_OFFSET + 4;
const uint16 UBOCamera::MAIN_LIT_DIR_OFFSET = UBOCamera::EXPOSURE_OFFSET + 4;
const uint16 UBOCamera::MAIN_LIT_COLOR_OFFSET = UBOCamera::MAIN_LIT_DIR_OFFSET + 4;
const uint16 UBOCamera::AMBIENT_SKY_OFFSET = UBOCamera::MAIN_LIT_COLOR_OFFSET + 4;
const uint16 UBOCamera::AMBIENT_GROUND_OFFSET = UBOCamera::AMBIENT_SKY_OFFSET + 4;
const uint16 UBOCamera::GLOBAL_FOG_COLOR_OFFSET = UBOCamera::AMBIENT_GROUND_OFFSET + 4;
const uint16 UBOCamera::GLOBAL_FOG_BASE_OFFSET = UBOCamera::GLOBAL_FOG_COLOR_OFFSET + 4;
const uint16 UBOCamera::GLOBAL_FOG_ADD_OFFSET = UBOCamera::GLOBAL_FOG_BASE_OFFSET + 4;
const uint16 UBOCamera::NEAR_FAR_OFFSET = UBOCamera::GLOBAL_FOG_ADD_OFFSET + 4;
const uint16 UBOCamera::VIEW_PORT_OFFSET = UBOCamera::NEAR_FAR_OFFSET + 4;
const uint16 UBOCamera::COUNT = UBOCamera::VIEW_PORT_OFFSET + 4;
const uint16 UBOCamera::SIZE = UBOCamera::COUNT*16;

const std::string UBOCamera::NAME{"CCCamera"};
const uint16 UBOCamera::BINDING = PipelineGlobalBindings::UBO_CAMERA;
const Gfx::DescriptorSetLayoutBinding UBOCamera::DESCRIPTOR = {
	UBOCamera::BINDING, Gfx::DescriptorType::UNIFORM_BUFFER, 1, Gfx::ShaderStageFlagBit::ALL,
};
const Gfx::UniformBlock UBOCamera::LAYOUT {
	SetIndex::GLOBAL, UBOCamera::BINDING, UBOCamera::NAME, 1, {
		{ "cc_matView", Gfx::Type::MAT4, 1},
		{ "cc_matViewInv", Gfx::Type::MAT4, 1},
		{ "cc_matProj", Gfx::Type::MAT4, 1},
		{ "cc_matProjInv", Gfx::Type::MAT4, 1},
		{ "cc_matViewProj", Gfx::Type::MAT4, 1},
		{ "cc_matViewProjInv", Gfx::Type::MAT4, 1},

		{ "cc_cameraPos", Gfx::Type::FLOAT4, 1},
		{ "cc_surfaceTransform", Gfx::Type::FLOAT4, 1},
		{ "cc_screenScale", Gfx::Type::FLOAT4, 1},
		{ "cc_exposure", Gfx::Type::FLOAT4, 1},
		{ "cc_mainLitDir", Gfx::Type::FLOAT4, 1},
		{ "cc_mainLitColor", Gfx::Type::FLOAT4, 1},
		{ "cc_ambientSky", Gfx::Type::FLOAT4, 1},
		{ "cc_ambientGround", Gfx::Type::FLOAT4, 1},
		{ "cc_fogColor", Gfx::Type::FLOAT4, 1},
		{ "cc_fogBase", Gfx::Type::FLOAT4, 1},
		{ "cc_fogAdd", Gfx::Type::FLOAT4, 1},
		{ "cc_nearFar", Gfx::Type::FLOAT4, 1},
		{ "cc_viewPort", Gfx::Type::FLOAT4, 1},
}
};

END_OGS_PIPLINE_NAMESPACE