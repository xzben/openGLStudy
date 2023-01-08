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
	//��ǰ��ȫ�ֺ궨�壬���ڿ����� IBL����Ч��ģ�顣
	std::unordered_map<std::string, MacroRecordItem> m_macros;
	//�����궨���ַ���������ʱȫ�̲���ı䣬���ڸ� shader ��һЩֻ��ƽ̨��صĲ�����
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