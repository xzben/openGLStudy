#include "Engine.h"
#include "rendersystem/GfxDevice.h"
BEGIN_OGS_NAMESPACE

Engine::Engine(const SharePtr<GameView>& gameview)
{
	m_device = getCurDvice();
	m_device->setGameView(gameview);
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

void Engine::render()
{

}

void Engine::preRender()
{
	
}

void Engine::postRender()
{
}

void Engine::draw()
{

}
void Engine::swapFrameBuffer()
{
	m_device->swapFrameBuffer();
}

END_OGS_NAMESPACE