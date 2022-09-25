#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE

enum class AssetType : int
{
	Unknow = -1,
	Lua,
	Txt,
	Json,
	Material,
	Model,
	Image,
	Shader,

	Prefab,
	Scene,
};

END_OGS_NAMESPACE