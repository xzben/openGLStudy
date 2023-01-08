#ifndef __2022_03_31_UTILS_H__
#define __2022_03_31_UTILS_H__

#include "define.h"
#include <string>

BEGIN_OGS_NAMESPACE
namespace Utils
{
	std::string string_format(const char* format, ...);
	std::string string_format_long(const char* foramt, ...);
	std::string create_guide();
	unsigned int random_num(const unsigned int max);

	template<typename T>
	void compute_hash(HASH_CODE& seed, const T& v);

	template<typename T>
	void hash_combine(HASH_CODE& seed, const T& v)
	{
		seed ^= std::hash<T> {}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template<typename T, typename ...Ts>
	void hash_combine(HASH_CODE& seed, const T& v, Ts... rest)
	{
		hash_combine(seed, v);
		if constexpr (sizeof...(Ts) > 1)
		{
			hash_combine(seed, rest...);
		}
	}
};

END_OGS_NAMESPACE
#endif//__2022_03_31_UTILS_H__