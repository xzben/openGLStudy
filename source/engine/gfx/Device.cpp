#include "Device.h"
#include "core/view/GameView.h"
#if RENDER_PLAT == RENDER_OPENGL3
#include "gfx/opengl3/OGL3Device.h"
#endif

BEGIN_OGS_GFX_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Device)

Device* Device::s_instance = nullptr;

Device* Device::getInstance()
{
	return s_instance;
}

Device::Device()
{
	s_instance = this;
}

Device* createCurDevice()
{
	Device* device = new OGL3Device;
	return device;
}

void Device::setGameView(GameView* gameview)
{
	m_gameview = gameview; 
}

AutoRef<Sampler> Device::getSamplerByHash(HASH_CODE hash)
{
	auto it = m_samplers.find(hash);
	if (it == m_samplers.end())
	{
		return nullptr;
	}
	return it->second;
}

Sampler* Device::addSampler(HASH_CODE hash, Sampler* sampler)
{
	m_samplers[hash] = sampler;
	return sampler;
}

END_OGS_GFX_NAMESPACE