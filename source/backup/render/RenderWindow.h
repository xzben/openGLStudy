#pragma once

#include "common.h"
#include "core/math/Rect.h"
#include "core/base/Notify.h"

BEGIN_OGS_NAMESPACE

class CameraComponent;
class FrameBuffer;
class Texture;

class RenderWindow : public Object
{
	DECLARE_CLASS(RenderWindow)
public:
	RenderWindow();
	virtual ~RenderWindow();

	void setViewport(const Rect& viewport);
	Rect& getViewport() { return m_viewport; }
	void setVisible(bool visible) { m_visible = visible; }
	bool isVisible() { return m_visible; }
	WeakRef<Texture> getRenderTarget();
	bool begin();
	void end();
public:
	Notify<const Rect&> EventViewportChange;
private:
	Rect m_viewport{0,0,0,0};
	bool m_visible{ true };
	FrameBuffer* m_framebuffer;
};

END_OGS_NAMESPACE
