#include "Renderable.h"
#include "core/systems/RenderSystem.h"

BEGIN_OGS_NAMESPACE

Renderable::Renderable()
{

}

Renderable::~Renderable()
{

}

void Renderable::onStart()
{
	RenderSystem::getInstance()->addRenderable(this);
}

void Renderable::onStop()
{
	RenderSystem::getInstance()->removeRenderable(this);
}

END_OGS_NAMESPACE