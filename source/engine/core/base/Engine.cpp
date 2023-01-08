#include "Engine.h"
#include "gfx/Device.h"
#include "core/systems/InputSystem.h"
#include "core/systems/RenderSystem.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Engine)

Engine::Engine()
{

}

Engine::~Engine()
{
	m_systems.clear();
	FileSystem::DestroyInstance();
	InputSystem::DestroyInstance();
}

System* Engine::addSystem(System* sys)
{
	m_systems.push_back(sys);

	return sys;
}

bool Engine::init()
{	
	addSystem(FileSystem::getInstance());
	addSystem(InputSystem::getInstance());
	addSystem(RenderSystem::create());

	return true;
}

void Engine::preRender()
{
	RenderSystem::getInstance()->preRender();
}
void Engine::render()
{
	RenderSystem::getInstance()->render();
}

void Engine::postRender()
{
	RenderSystem::getInstance()->postRender();
}

void Engine::draw()
{
	RenderSystem::getInstance()->draw();
}

void Engine::update(float dt)
{
	for (AutoRef<System>& sys : m_systems)
	{
		sys->update(dt);
	}
}

END_OGS_NAMESPACE