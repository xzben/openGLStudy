#include "utils/Utils.h"
#include <stdarg.h>

std::string Utils::string_format(const char* format, ...)
{
	char buff[1024] = { 0 };

	va_list args;
	va_start(args, format);
	vsprintf_s(buff, sizeof(buff), format, args);
	va_end(args);

	std::string str(buff);
	return str;
}

std::string Utils::string_format_long(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int count = vsnprintf(NULL, 0, format, args); // 使用vsnprintf：warning C4996; 使用vsnprintf_s：无法自动计算长度
	va_end(args);

	va_start(args, format);
	char* buff = (char*)malloc(count * sizeof(wchar_t));
	vsnprintf(buff, count, format, args);
	va_end(args);

	std::string str(buff, count);
	free(buff);
	return str;
}