#pragma once

#include "common.h"
#include "core/render/GfxObject.h"
#include "render_macro.h"
#include "core/math/math.h"

BEGIN_OGS_NAMESPACE

class AssetImage;

class Texture : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Texture)
public:
	friend class FrameBuffer;

	static Texture* createAttatchColor(Size* size = nullptr);
	Texture();
	~Texture();
	bool initWithFile(const std::string& filename);
	bool initWithImageData(AssetImage* image);
	void setSize(const Size& size);
	void setUsage(TextureUsage usage) { m_usage = usage; }
	void setSampeType(TextureSampleType type) { m_sampleType = type; }
	void setIndex(int index) { m_index = index; }
	void setSampleTypeName(const std::string& name) { m_sampleTypeName = name; }
protected:
	void updateSampeInfo();
	void updateData();
	void initWithColorAttachment(Size* size = nullptr);
	void initWithDepth24Stencil8Attachment(Size* size = nullptr);
protected:
	AutoRef<AssetImage> m_image;
	Size m_size;
	TextureFormat m_format{ TextureFormat::RGBA8 };
	SampleInfo m_sampeinfo;
	TextureUsage m_usage{TextureUsage::SAMPLED};
	TextureSampleType m_sampleType{ TextureSampleType::DIFFUSE };
	int m_index{ 0 };
	std::string m_sampleTypeName{ "diffues" };
};

END_OGS_NAMESPACE