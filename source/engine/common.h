#ifndef __COMMON_2021_09_06_H__
#define __COMMON_2021_09_06_H__
#include <string>
#include <vector>
#include <cassert>

#include "define.h"
#include "define/shader_define.h"

typedef unsigned int  uint;
typedef unsigned char byte;
typedef unsigned int  GL_HANDLE;

#define GL_ERROR_MSG_SIZE 512  //openGL 错误信息日志buff size

#define PI 3.14159265359

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