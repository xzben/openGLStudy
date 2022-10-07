#pragma once
#include "common.h"
#include <vector>
#include <string>

BEGIN_OGS_NAMESPACE

class ReflexEnumItem
{
public:
	ReflexEnumItem(const std::string& n, int v)
		:name(n)
		,value(v)
	{

	}
	std::string name;
	int  value;
};

template<typename Enum>
class ReflexEnumDesc
{
public:
	using ItemType = ReflexEnumItem<Enum>;
	ReflexEnumDesc(const std::string& name, std::vector<ItemType> items)
		: m_name(name)
		, m_values(items)
	{

	}
protected:
	std::string m_name;
	std::vector<ItemType> m_values;
};

END_OGS_NAMESPACE