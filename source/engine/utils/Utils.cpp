#include "utils/Utils.h"
#include <stdarg.h>
#include <string>
#include <random>
#include "core/tool/Time.h"

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

unsigned int Utils::random_num(const unsigned int max) 
{
   std::random_device rd;
   std::mt19937 gen(rd());
   
   std::uniform_int_distribution<> dis(0, max);
   return dis(gen);
}

std::string Utils::create_guide()
{
	int len = 20;
	time_t Data1 = OGS::Time::get_time_stamp_microsec();
	unsigned short Data3 = random_num(0xffff);
	unsigned short Data4 = random_num(0xffff);
	unsigned char  Data5[8];
	for (int i = 0; i < 8; i++)
		Data5[i] = random_num(0xff);
	
	static char buf[64] = { 0 };
	sprintf_s(buf, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		Data1, Data3, Data4, Data5[0], Data5[1],
		Data5[2], Data5[3], Data5[4], Data5[5],
		Data5[6], Data5[7]);
	return buf;
}