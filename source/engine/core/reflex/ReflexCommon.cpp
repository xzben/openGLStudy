#include "ReflexCommon.h"
#include "json/json.h"

BEGIN_OGS_NAMESPACE
namespace FieldSerialize
{
	template<>
	bool Serialize<int>(JSON& json, int* field)
	{
		json = *field;
		return true;
	}

	template<>
	bool Deserialize<int>(const JSON& json, int* field)
	{
		*field = json.asInt();
		return true;
	}

	template<> 
	bool Serialize<bool>(JSON& json, bool* field)
	{
		json = *field;
		return true;
	}
	template<> 
	bool Deserialize<bool>(const JSON& json, bool* field)
	{
		*field = json.asBool();
		return true;
	}

	template<> 
	bool Serialize<std::string>(JSON& json, std::string* field)
	{
		json = *field;
		return true;
	}
	template<> 
	bool Deserialize<std::string>(const JSON& json, std::string* field)
	{
		*field = json.asCString();
		return true;
	}

	template<> 
	bool Serialize<float>(JSON& json, float* field)
	{
		json = *field;
		return true;
	}
	template<> 
	bool Deserialize<float>(const JSON& json, float* field)
	{
		*field = json.asFloat();
		return true;
	}

	template<>
	bool Serialize<double>(JSON& json, double* field)
	{
		json = *field;
		return true;
	}

	template<>
	bool Deserialize<double>(const JSON& json, double* field)
	{
		*field = json.asDouble();
		return true;
	}

	template<>
	bool Serialize<unsigned int>(JSON& json, unsigned int* field)
	{
		json = *field;
		return true;
	}
	template<> 
	bool Deserialize<unsigned int>(const JSON& json, unsigned int* field)
	{
		*field = json.asUInt();
		return true;
	}
#if defined(JSON_HAS_INT64)
	template<>
	bool Serialize<JSON::UInt64>(JSON& json, JSON::UInt64* field)
	{
		json = *field;
		return true;
	}
	template<>
	bool Deserialize<JSON::UInt64>(const JSON& json, JSON::UInt64* field)
	{
		*field = json.asUInt64();
		return true;
	}

	template<>
	bool Serialize<JSON::Int64>(JSON& json, JSON::Int64* field)
	{
		json = *field;
		return true;
	}

	template<>
	bool Deserialize<JSON::Int64>(const JSON& json, JSON::Int64* field)
	{
		*field = json.asInt64();
		return true;
	}
#endif
}

END_OGS_NAMESPACE