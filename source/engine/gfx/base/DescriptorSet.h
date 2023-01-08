#pragma once

#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class DescriptSetLayout;
class Buffer;
class Texture;
class Sampler;

class DescriptorSet : public GfxObject
{
	DECLARE_RUNTIME_CLASS(DescriptorSet)
public:
	DescriptorSet():GfxObject(ObjectType::DESCRIPTOR_SET){}

	void update() {}
	void bindBuffer(uint32 binding, Buffer* texture, uint32 index = 0);
	void bindSampler(uint32 binding, Sampler* texture, uint32 index = 0);
	void bindTexture(uint32 binding, Texture* texture, uint32 index = 0);
	Buffer*  getBuffer(uint32 binding, uint32 index = 0);
	Sampler* getSampler(uint32 binding, uint32 index = 0);
	Texture* getTexture(uint32 binding, uint32 index = 0);
protected:
	AutoRef<DescriptSetLayout> m_layout;
	std::vector<Buffer*>		   m_buffers;
	std::vector<Texture*>	   m_textures;
	std::vector<Sampler*>	   m_samplers;
};

END_OGS_GFX_NAMESPACE