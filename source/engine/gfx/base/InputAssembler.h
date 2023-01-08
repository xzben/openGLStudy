#pragma once

#include "GfxObject.h"
#include "utils/Utils.h"
BEGIN_OGS_GFX_NAMESPACE

class Buffer;

class DrawInfo
{
public:
	uint32 vertexCount{ 0 };
	uint32 firstVertex{ 0 };
	uint32 indexCount{ 0 };
	uint32 firstIndex{ 0 };
	uint32 vertexOffset{ 0 };
	uint32 instanceCount{ 0 };
	uint32 firstInstance{ 0 };
};

class InputAssemblerInfo
{
public:
	std::vector<Attribute> attributes;
	std::vector<AutoRef<Buffer>> vertexBuffers;
	AutoRef<Buffer> indexBuffer;
	AutoRef<Buffer> indirectBuffer;
};

class InputAssembler : public GfxObject
{
	DECLARE_RUNTIME_CLASS(InputAssembler)
public:
	InputAssembler():GfxObject(ObjectType::INPUT_ASSEMBLER){}
	virtual ~InputAssembler() {}
	virtual void active() = 0;
	virtual void deactive() = 0;
	virtual bool initialize(const InputAssemblerInfo& info) = 0;
	
	HASH_CODE computeAttributeHash()
	{
		HASH_CODE seed = 0;
		for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
		{
			Attribute& ab = *it;
			Utils::compute_hash<Attribute>(seed, ab);
		}

		return seed;
	}
protected:
	HASH_CODE						m_attribteHash{ 0 };
	std::vector<Attribute>			m_attributes;
	std::vector<AutoRef<Buffer>>	m_vertexBuffers;
	AutoRef<Buffer>					m_indexBuffer;
	AutoRef<Buffer>					m_indirectBuffer;
	AutoRef<DrawInfo>				m_drawInfo;
};
END_OGS_GFX_NAMESPACE