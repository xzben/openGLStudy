#include"RenderWindow.h"
#include "core/systems/RenderSystem.h"
#include "core/render/FrameBuffer.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(RenderWindow)
IMPLEMENT_REFLEX_CLASS_BASE(RenderWindow)

RenderWindow::RenderWindow()
{
	RenderSystem::getInstance()->addRenderWindow(this);
	m_framebuffer = new FrameBuffer();
}

RenderWindow::~RenderWindow()
{
	RenderSystem::getInstance()->removeRenderWindow(this);
}

void RenderWindow::setViewport(const Rect& viewport)
{
	if (m_viewport == viewport) return;
	m_viewport = viewport;
	m_framebuffer->setSize(m_viewport.getSize());
	EventViewportChange.emit(viewport);
}

bool RenderWindow::begin()
{
	if (!m_visible) return false;
	m_framebuffer->active();
	return true;
}

void RenderWindow::end()
{
	m_framebuffer->deactive();
}

WeakRef<Texture> RenderWindow::getRenderTarget()
{
	if (m_framebuffer) {
		return m_framebuffer->getColorTexture(0);
	}
	return nullptr;
}

END_OGS_NAMESPACE