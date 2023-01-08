#include "ForwardPipeline.h"
#include "pipeline/shadow/ShadowFlow.h"
#include "pipeline/foward/FowardFlow.h"

BEGIN_OGS_PIPLINE_NAMESPACE

ForwardPipeline::ForwardPipeline()
{

}

ForwardPipeline::~ForwardPipeline()
{

}

bool ForwardPipeline::initialize()
{
	//auto shadowFlow = ShadowFlow::create();
	//shadowFlow->initialize();
	//this->m_flows.push_back(shadowFlow);

	auto forwardFlow = ForwardFlow::create();
	forwardFlow->initialize();
	this->m_flows.push_back(forwardFlow);

	return true;
}

bool ForwardPipeline::active()
{
	return true;
}

void ForwardPipeline::destroy()
{

}

END_OGS_PIPLINE_NAMESPACE