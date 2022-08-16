#include "ReflexCommon.h"
#include "json/json.h"

BEGIN_OGS_NAMESPACE
namespace FieldSerialize
{
	template<>
	void Serialize(JSON& json, int* field)
	{
		json = *field;
	}

	template<>
	void Deserialize(const JSON& json, int* field)
	{
		*field = json.asInt();
	}

	template<> void Serialize(JSON& json, bool* field)
	{
		json = *field;
	}
	template<> void Deserialize(const JSON& json, bool* field)
	{
		*field = json.asBool();
	}

	template<> void Serialize(JSON& json, std::string* field)
	{
		json = *field;
	}
	template<> void Deserialize(const JSON& json, std::string* field)
	{
		*field = json.asCString();
	}

	template<> void Serialize(JSON& json, float* field)
	{
		json = *field;
	}
	template<> void Deserialize(const JSON& json, float* field)
	{
		*field = json.asFloat();
	}

	template<> void Serialize(JSON& json, double* field)
	{
		json = *field;
	}

	template<> void Deserialize(const JSON& json, double* field)
	{
		*field = json.asDouble();
	}

	template<> void Serialize(JSON& json, unsigned int* field)
	{
		json = *field;
	}
	template<> void Deserialize(const JSON& json, unsigned int* field)
	{
		*field = json.asUInt();
	}
#if defined(JSON_HAS_INT64)
	template<> void Serialize(JSON& json, JSON::UInt64* field)
	{
		json = *field;
	}
	template<> void Deserialize(const JSON& json, JSON::UInt64* field)
	{
		*field = json.asUInt64();
	}

	template<> void Serialize(JSON& json, JSON::Int64* field)
	{
		json = *field;
	}

	template<> void Deserialize(const JSON& json, JSON::Int64* field)
	{
		*field = json.asInt64();
	}
#endif
}

END_OGS_NAMESPACE