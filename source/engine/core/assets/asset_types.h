#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE

enum AssetType
{
	TUnknow = -1,
	TLua,
	TTxt,
	TJson,
	TMaterial,
	TModel,
	TImage,
	TShader,

	TPrefab,
	TScene,
};

END_OGS_NAMESPACE