#pragma once

#include "common.h"

BEGIN_OGS_GFX_NAMESPACE

class Attribute
{
public:
	std::string name;
	Format  format{ Format::UNKNOWN };
	bool    isNormalized;
	uint32  stream;
	bool    isInstanced;
	uint16  location;
};

END_OGS_GFX_NAMESPACE