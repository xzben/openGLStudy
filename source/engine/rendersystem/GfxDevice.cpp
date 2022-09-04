#include "GfxDevice.h"

#if RENDER_PLAT == RENDER_OPENGL3
#include "rendersystem/opengl3/OGL3Device.h"
#endif
BEGIN_OGS_NAMESPACE

static GfxDevice* s_device = nullptr;

GfxDevice* getCurDvice()
{
	if (s_device) return s_device;

#if RENDER_PLAT == RENDER_OPENGL3
	s_device = new OGL3Device();
#endif
	return s_device;
}

END_OGS_NAMESPACE