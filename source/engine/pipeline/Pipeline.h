#ifndef __2022_04_18_PIPELINE_H__
#define __2022_04_18_PIPELINE_H__

#include "common.h"
#include "core/base/Object.h"
#include "pipeline/pipeline_define.h"
#include "core/math/math.h"

BEGIN_OGS_GFX_NAMESPACE
class CommandBuffer;
class RenderPass;
END_OGS_GFX_NAMESPACE

BEGIN_OGS_PIPLINE_NAMESPACE

class RenderFlow;

class RenderPipeline : public Object
{
protected:
	std::string m_name;
	uint32  m_tag;
	std::vector<AutoRef<RenderFlow>> m_flows;
	//当前的全局宏定义，用于控制如 IBL、雾效等模块。
	std::unordered_map<std::string, MacroRecordItem> m_macros;
	//常量宏定义字符串，运行时全程不会改变，用于给 shader 传一些只和平台相关的参数。
	std::string m_constMacros{ "" }; 

	uint16 m_width;
	uint16 m_height;
	Rect   m_lastUsedRenderRect;
	std::vector<AutoRef<OGS::Gfx::CommandBuffer>> m_commandBuffers;
	std::unordered_map<int32, AutoRef<OGS::Gfx::RenderPass>> m_renderPass;
public:
	RenderPipeline();
	virtual ~RenderPipeline();
};

END_OGS_PIPLINE_NAMESPACE
#endif//__2022_04_18_PIPELINE_H__