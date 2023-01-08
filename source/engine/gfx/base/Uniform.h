#pragma once

#include "gfx/base/gfx_base_define.h"
#include <vector>
BEGIN_OGS_GFX_NAMESPACE

class UniformItem
{
public:
	uint16      set{0};
	uint16		binding{ 0 };
	std::string name{ "" };
	uint16      count{ 0 };
};

class Uniform
{
public:
	std::string name{ "" };
	Type        type{ Type::UNKNOWN };
	uint16      count{ 0 };
};

class UniformBlock : public UniformItem
{
public:
	std::vector<Uniform> members;
};

class UniformSamplerTexutre : public UniformItem
{
public:
	Type   type{ Type::UNKNOWN };
};

class UniformSampler : public UniformItem
{
public:

};

class UniformTexture : public UniformItem
{
public:
	Type   type{ Type::UNKNOWN };
};

class UniformStorageImage : public UniformItem
{
public:
	Type   type{ Type::UNKNOWN };
	MemoryAccessBit memoryAccess{MemoryAccessBit::READ_WRITE};
};

class UniformStorageBuffer : public UniformItem
{
public:
	MemoryAccessBit memoryAccess{ MemoryAccessBit::READ_WRITE };
};

class UniformInputAttchment : public UniformItem
{
public:
};

END_OGS_GFX_NAMESPACE