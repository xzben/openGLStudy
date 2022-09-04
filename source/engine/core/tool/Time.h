#pragma once
#include "common.h"
#include <ctime>

BEGIN_OGS_NAMESPACE
class Time : public std::tm
{
public:
	static time_t  get_time_stamp_sec();
	static time_t  get_time_stamp_millisec();
	static time_t  get_time_stamp_microsec();

	Time();
	int getYear() { this->tm_year; }
	int tm_millisec; // ∫¡√Î
	int tm_microsec; // Œ¢√Î
};

END_OGS_NAMESPACE