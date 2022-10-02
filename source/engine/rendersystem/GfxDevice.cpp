#include "GfxDevice.h"
#include "core/view/GameView.h"
#if RENDER_PLAT == RENDER_OPENGL3
#include "rendersystem/opengl3/OGL3Device.h"
#endif
BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GfxDevice)

GfxDevice* createCurDevice()
{
	GfxDevice* device = new OGL3Device;
	return device;
}

void GfxDevice::setGameView(GameView* gameview)
{
	m_gameview = gameview; 
}

END_OGS_NAMESPACE