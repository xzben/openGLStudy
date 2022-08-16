#pragma once

#include "ReflexItem.h"

BEGIN_OGS_NAMESPACE

namespace FieldSerialize
{
	template<> void Serialize(JSON& json, int* field);
	template<> void Deserialize(const JSON& json, int* field);

	template<> void Serialize(JSON& json, bool* field);
	template<> void Deserialize(const JSON& json, bool* field);

	template<> void Serialize(JSON& json, std::string* field);
	template<> void Deserialize(const JSON& json, std::string* field);

	template<> void Serialize(JSON& json, float* field);
	template<> void Deserialize(const JSON& json, float* field);

	template<> void Serialize(JSON& json, double* field);
	template<> void Deserialize(const JSON& json, double* field);

	template<> void Serialize(JSON& json, unsigned int* field);
	template<> void Deserialize(const JSON& json, unsigned int* field);
#if defined(JSON_HAS_INT64)
	template<> void Serialize(JSON& json, JSON::UInt64* field);
	template<> void Deserialize(const JSON& json, JSON::UInt64* field);

	template<> void Serialize(JSON& json, JSON::Int64* field);
	template<> void Deserialize(const JSON& json, JSON::Int64* field);
#endif
}
END_OGS_NAMESPACE
