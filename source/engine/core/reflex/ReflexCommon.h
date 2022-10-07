#pragma once

#include "ReflexItem.h"
#include "math/math.h"
BEGIN_OGS_NAMESPACE

namespace FieldSerialize
{
	template<>
	bool Serialize<int>(JSON& json, int* field);
	template<>
	bool Deserialize<int>(const JSON& json, int* field);

	template<>
	bool Serialize<bool>(JSON& json, bool* field);
	template<>
	bool Deserialize<bool>(const JSON& json, bool* field);

	template<>
	bool Serialize<std::string>(JSON& json, std::string* field);
	template<>
	bool Deserialize<std::string>(const JSON& json, std::string* field);

	template<>
	bool Serialize<float>(JSON& json, float* field);
	template<>
	bool Deserialize<float>(const JSON& json, float* field);

	template<>
	bool Serialize<double>(JSON& json, double* field);
	template<>
	bool Deserialize<double>(const JSON& json, double* field);

	template<>
	bool Serialize<unsigned int>(JSON& json, unsigned int* field);
	template<>
	bool Deserialize<unsigned int>(const JSON& json, unsigned int* field);

#if defined(JSON_HAS_INT64)
	template<>
	bool Serialize<JSON::UInt64>(JSON& json, JSON::UInt64* field);
	template<>
	bool Deserialize<JSON::UInt64>(const JSON& json, JSON::UInt64* field);

	template<>
	bool Serialize<JSON::Int64>(JSON& json, JSON::Int64* field);
	template<>
	bool Deserialize<JSON::Int64>(const JSON& json, JSON::Int64* field);

#endif
}
END_OGS_NAMESPACE
