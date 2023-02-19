#pragma once

#include "GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE


class ShaderStage : public GfxObject
{
	DECLARE_RUNTIME_CLASS(ShaderStage)
public:
	ShaderStageFlagBit stage{ ShaderStageFlagBit::NONE };
	std::string        source;
};

class ShaderInfo : public Object
{
public:
	std::string name;
	std::vector<AutoRef<ShaderStage>> stages;
	std::vector<AutoRef<Attribute>>  attributes;
	std::vector<AutoRef<UniformBlock>> blocks;
	std::vector<AutoRef<UniformStorageBuffer>> buffers;
	std::vector<AutoRef<UniformSamplerTexutre>> samplerTextures;
	std::vector<AutoRef<UniformSampler>> samplers;
	std::vector<AutoRef<UniformTexture>> textures;
	std::vector<AutoRef<UniformStorageImage>> images;
	std::vector<AutoRef<UniformInputAttchment>> subpassInputs;
};

class Shader : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Shader)
public:
	Shader() :GfxObject(ObjectType::SHADER) {}
	virtual ~Shader() {}

	const std::vector<AutoRef<Attribute>>& getAttributes() { return m_info->attributes; }
	const std::vector<AutoRef<UniformBlock>>& getBlocks() { return m_info->blocks; }
	const std::vector<AutoRef<UniformSampler>>& getSamplers() { return m_info->samplers; }
	const std::string getName() { return m_info->name; }

	virtual bool initilize(ShaderInfo* info) { m_info = info; return true; }
protected:
	AutoRef<ShaderInfo> m_info;
};

END_OGS_GFX_NAMESPACE