#include "GfxDevice.h"
#if RENDER_PLAT == RENDER_OPENGL3
#include "rendersystem/opengl3/OGL3Device.h"
#endif
BEGIN_OGS_NAMESPACE

SharePtr<GfxDevice> createCurDevice()
{
	SharePtr<GfxDevice> device = makeShare((GfxDevice*)new OGL3Device);

	return device;
}

END_OGS_NAMESPACE