#pragma once

#include "gfx/base/GfxObject.h"

BEGIN_OGS_GFX_NAMESPACE

class Sampler : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Sampler)
public:
	static HASH_CODE computeHash(SamplerInfo* info)
	{
		HASH_CODE hash = (HASH_CODE)info->minFilter;

		hash |= ((HASH_CODE)info->magFilter << 2);
		hash |= ((HASH_CODE)info->mipFilter << 4);
		hash |= ((HASH_CODE)info->addressU << 6);
		hash |= ((HASH_CODE)info->addressV << 8);
		hash |= ((HASH_CODE)info->addressW << 10);
		hash |= ((HASH_CODE)info->maxAnisotropy << 12);
		hash |= ((HASH_CODE)info->cmpFunc << 16);

		return hash;
	}

	static SamplerInfo* unpackFromHash(HASH_CODE hash)
	{
		SamplerInfo* info = new SamplerInfo();

		info->minFilter = Filter((hash & ((1 << 2) - 1)) >> 0);
		info->magFilter = Filter((hash & ((1 << 2) - 1)) >> 2);
		info->mipFilter = Filter((hash & ((1 << 2) - 1)) >> 4);
		info->addressU = Address((hash & ((1 << 2) - 1)) >> 6);
		info->addressV = Address((hash & ((1 << 2) - 1)) >> 8);
		info->addressW = Address((hash & ((1 << 2) - 1)) >> 10);
		info->maxAnisotropy = uint32((hash & ((1 << 4) - 1)) >> 12);
		info->cmpFunc = ComparisonFunc((hash & ((1 << 3) - 1)) >> 16);

		return info;
	}

	Sampler(SamplerInfo* info, HASH_CODE hash) :GfxObject(ObjectType::SAMPLER) 
	{
		m_info = new SamplerInfo();
		m_info->copy(*info);
		m_hash = hash;
	}

	virtual ~Sampler() 
	{}

	HASH_CODE getHash() { return m_hash; }
	AutoRef<SamplerInfo> getInfo() { return m_info; }
protected:
	AutoRef<SamplerInfo> m_info;
	HASH_CODE m_hash;
};
END_OGS_GFX_NAMESPACE