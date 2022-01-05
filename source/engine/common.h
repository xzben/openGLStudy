#ifndef __COMMON_2021_09_06_H__
#define __COMMON_2021_09_06_H__
#include <string>
#include <vector>
#include <cassert>

#include "math/math.h"

typedef unsigned int  uint;
typedef unsigned char byte;


#if CC_DISABLE_ASSET
	#define CC_ASSET( cond )
#else
	#define CC_ASSET( cond ) assert((cond))
#endif

#define PLAT_WIN		1
#define PLAT_ANDROID	2
#define PLAT_IOS		3
#define PLAT_MAC		4


#define CUR_PLAT		PLAT_WIN


#define CREATE_FUNC( CLS_NAME ) \
	static CLS_NAME* create(){ \
		CLS_NAME* obj = new CLS_NAME(); \
		obj->doLoad(); \
		return obj; \
	}

#endif//__COMMON_2021_09_06_H__