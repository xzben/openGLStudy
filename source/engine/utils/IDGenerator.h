#pragma once

#include "define.h"
#include "Utils.h"
BEGIN_OGS_NAMESPACE

class IDGenerator
{
public:
	static IDGenerator global;
public:
	IDGenerator(std::string category)
	{
		m_prefix = category;
	}

	std::string getNewId()
	{
		return Utils::string_format("%s.%d", m_prefix.c_str(), ++m_id);
	}
protected:
	uint32 m_id{0};
	std::string m_prefix;
};

END_OGS_NAMESPACE