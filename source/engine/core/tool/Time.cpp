#include "Time.h"
#include <ctime>
#include <chrono>

BEGIN_OGS_NAMESPACE

time_t Time::get_time_stamp_sec()
{
	return get_time_stamp_microsec() / 1000000;
}

time_t Time::get_time_stamp_millisec()
{
	return get_time_stamp_microsec() / 1000;
}

time_t  Time::get_time_stamp_microsec()
{
	std::chrono::time_point time_point_now = std::chrono::system_clock::now(); // 获取当前时间点
	std::chrono::system_clock::duration duration_since_epoch = time_point_now.time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
	time_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count(); // 将时长转换为微秒数
	
	return microseconds_since_epoch;
}

Time::Time()
{
	std::chrono::time_point time_point_now = std::chrono::system_clock::now(); // 获取当前时间点
	std::chrono::system_clock::duration duration_since_epoch = time_point_now.time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
	time_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count(); // 将时长转换为微秒数
	time_t seconds_since_epoch = microseconds_since_epoch / 1000000; // 将时长转换为秒数

	tm_microsec = microseconds_since_epoch % 1000;
	tm_millisec = microseconds_since_epoch / 1000 % 1000;
#if defined _MSC_VER && _MSC_VER >= 1400
	localtime_s(this, &seconds_since_epoch);
#elif defined __GNUC__
	localtime_r(&seconds_since_epoch, this);
#else
	std::tm* self = this;
	*self = *std::localtime(&seconds_since_epoch);
#endif
}

END_OGS_NAMESPACE