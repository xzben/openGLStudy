#pragma once


#include "define.h"
#include "reflex_define.h"
#include "reflexClass.h"
#include "ReflexClassField.h"
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <string>
#include <map>

BEGIN_OGS_NAMESPACE
class Object;

namespace FieldSerialize
{
	template<typename FieldType>
	bool Serialize(JSON& json, FieldType* field)
	{
		return FieldType::GetREFLEX()->Serialize(field, json);
	}

	template<typename FieldType>
	bool Deserialize(const JSON& json, FieldType* field)
	{
		return FieldType::GetREFLEX()->Deserialize(field, json);
	}

	template<typename FieldType>
	bool Serialize(JSON& json, std::vector<FieldType>*field)
	{
		int size = field->size();
		json.resize(size);

		for (int i = 0; i < size; i++)
		{
			if (!FieldSerialize::Serialize(json[i], &((*field)[i])))
			{
				return false;
			}
		}
		return true;
	}

	template<typename FieldType>
	bool Deserialize(const JSON& json, std::vector<FieldType>* field)
	{
		ASSERT(json.isArray(), "must been array json object");

		int count = json.size();
		field->resize(count);
	
		for (int i = 0; i < count; i++)
		{
			if (!FieldSerialize::Deserialize(json[i], &((*field)[i])))
			{
				return false;
			}
		}

		return true;
	}

	/*
	template<typename KeyType, typename FieldType>
	void Serialize(JSON& json, std::map<reflex_define::valid_mapkey_t<KeyType>, FieldType>* field)
	{
		int size = field->size();
		json.resize(size);
		int index = 0;
		for(auto it = field->begin(); it != field->end(); it++)
		{
			JSON item = json[index];
			FieldSerialize::Serialize(item[MAP_KEY], &it->first);
			FieldSerialize::Serialize(item[MAP_VALUE], &it->second);
			index++;
		}
	}

	template<typename KeyType, typename FieldType>
	void Deserialize(const JSON& json, std::map<reflex_define::valid_mapkey_t<KeyType>, FieldType>* field)
	{
		ASSERT(json.isArray(), "must been array json object");
		int size = json.size();
		for (int i = 0; i < size; i++)
		{
			KeyType key;
			FieldType value;

			const JSON& item = json[i];
			ASSERT(item.isObject(), "must been map object has key and value");
			FieldSerialize::Deserialize(item[MAP_KEY], &key);
			FieldSerialize::Deserialize(item[MAP_VALUE], &value);

			field->insert(std::make_pair(key, value));
		}
	}*/
}

class StaticRunObject
{
public:
	using AutoFunc = std::function<void(void)>;
	StaticRunObject(AutoFunc func) {
		func();
	}
};

END_OGS_NAMESPACE
