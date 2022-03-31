#ifndef __2022_03_31_UTILS_H__
#define __2022_03_31_UTILS_H__

#include <string>

class Utils
{
public:
	static std::string string_format(const char* format, ...);
	static std::string string_format_long(const char* foramt, ...);
};
#endif//__2022_03_31_UTILS_H__