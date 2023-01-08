#pragma once

#include "gfx_base_define.h"
#include "GfxObject.h"
#include "core/math/math.h"

BEGIN_OGS_GFX_NAMESPACE

//光栅化阶段
struct RasterizerState
{
public:
	bool isDiscard;
	PolygonMode polygonModel;
	CullMode cullMode;
	bool isFrontFaceCCW; //是否顺时针是正面
	bool depthDiasEnable;
	int depthBias;
	int depthDiasClamp;
	int depthDiasSlop;
	bool isDepthClip;
	bool isMultisampel;
	uint16 lineWidth;
};


struct DepthStencilState
{
public:
	bool depthTest;
	bool depthWrite;
	ComparisonFunc depthFunc{ ComparisonFunc::LESS };

	bool stencilTestFront;
	ComparisonFunc stencilFuncFront{ ComparisonFunc::ALWAYS };
	uint16 stencilReadMaskFront{ 0xffff };
	uint16 stencilWriteMaskFront{ 0xffff };
	StencilOp stencilFailOpFront{ StencilOp::KEEP };
	StencilOp stencilZFailOpFront{ StencilOp::KEEP };
	StencilOp stencilPassOpFront{ StencilOp::KEEP };
	uint16 stencilRefFront{ 1 };
	bool  stencilTestBack{ false };

	ComparisonFunc stencilFuncBack{ ComparisonFunc::ALWAYS };
	uint16 stencilReadMaskBack{ 0xffff };
	uint16 stencilWriteMaskBack{ 0xffff };
	StencilOp stencilFailOpBack{ StencilOp::KEEP };
	StencilOp stencilZFailOpBack{ StencilOp::KEEP };
	StencilOp stencilPassOpBack{ StencilOp::KEEP };
	uint16 stencilRefBack{ 1 };
};


struct BlendTarget
{
public:
	bool blend;
	BlendFactor blendSrc{ BlendFactor::ONE };
	BlendFactor blendDst{ BlendFactor::ZERO };
	BlendOp     blendEq{ BlendOp::ADD };
	BlendFactor blendSrcAlpha{ BlendFactor::ONE };
	BlendFactor blendDstAplha{ BlendFactor::ZERO };
	BlendOp     blendAlphaEq{ BlendOp::ADD };
	ColorMask	blendColorMask{ ColorMask::ALL };
};

struct BlendState
{
public:
	bool isA2C;
	bool isIndepend;
	Color blendColor;
	std::vector<BlendTarget> targets;
};

class Shader;
class PipelineLayout;
class RenderPass;

class InputState
{
public:
	std::vector<AutoRef<Attribute>> attributes;
};

class PipelineStateInfo
{
public:
	AutoRef<Shader> shader;
	AutoRef<PipelineLayout> pipelineLayout;
	AutoRef<RenderPass> rendeerPass;
	AutoRef<InputState> inputState;
	AutoRef<RasterizerState> rasterizerState;
	AutoRef<DepthStencilState> depthStencilState;
	BlendState blendState;
	PrimitiveMode primitive;
	DynamicStateFlagBit dynamicStates;
	PipelineBindPoint bindPoint;
};

class PipelineState : public GfxObject
{
	DECLARE_RUNTIME_CLASS(PipelineState)
public:
	PipelineState() :GfxObject(ObjectType::PIPELINE_STATE) {}
protected:
	AutoRef<Shader>				m_shader;
	AutoRef<PipelineLayout>		m_pipelineLayout;
	PrimitiveMode				m_primitive{PrimitiveMode::TRIANGLE_LIST};
	AutoRef<InputState>			m_is;
	AutoRef<RasterizerState>	m_rs;
	AutoRef<DepthStencilState>  m_dss;
	BlendState			m_bs;
	DynamicStateFlagBit			m_dynamicStates;
	AutoRef<RenderPass>			m_renderPass;
};

END_OGS_GFX_NAMESPACE