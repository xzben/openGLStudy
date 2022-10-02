#include "Engine.h"
#include "rendersystem/GfxDevice.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Engine)

Engine::Engine()
{

}

Engine::~Engine()
{
}

bool Engine::init()
{	
	return true;
}

void Engine::update(float dt)
{

}

END_OGS_NAMESPACE