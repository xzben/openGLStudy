#pragma once
#include "define.h"
#include "innerJson.h"
BEGIN_OGS_NAMESPACE

namespace reflex_define
{
	template <class _Ty>
	using valid_mapkey_t = std::enable_if_t<std::_Is_any_of_v<_Ty, bool, char, int, unsigned int, float, double, JSON::Int64, JSON::UInt64, std::string>, _Ty>;
}

#define CLASS_OBJ_KEY	"classname"
#define CLASS_SUPER_KEY "superclass"
#define MAP_KEY  "map_key"
#define MAP_VALUE  "map_value"


END_OGS_NAMESPACE