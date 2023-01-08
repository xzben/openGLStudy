#pragma once

#include "gfx/base/states/sampler.h"
#include "gfx/opengl3/gl3_define.h"
#include <unordered_map>

BEGIN_OGS_GFX_NAMESPACE
class GL3Sampler : public Sampler
{
public:
	GL3Sampler(SamplerInfo* info, HASH_CODE hash);
	virtual ~GL3Sampler();
	GLuint getGLSampler(uint16 minlod, uint16 maxLod);
public:
	std::unordered_map<HASH_CODE, GLuint> m_cache;
};
END_OGS_GFX_NAMESPACE