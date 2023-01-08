#pragma once

#include "define.h"

BEGIN_OGS_PIPLINE_NAMESPACE

struct MacroRecordItem
{
public:
	MacroRecordItem(int32 value) :type(Type::INT), intValue(value) {}
	MacroRecordItem(bool value) :type(Type::BOOL), boolValue(value) {}
	MacroRecordItem(std::string value) :type(Type::STRING), strValue(value) {}
	~MacroRecordItem() {}
protected:
	enum Type
	{
		INT,
		BOOL,
		STRING,
	};

	Type type;
	union
	{
		int32  intValue;
		bool   boolValue;
		std::string strValue;
	};
};

END_OGS_PIPLINE_NAMESPACE