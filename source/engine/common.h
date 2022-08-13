#ifndef __COMMON_2021_09_06_H__
#define __COMMON_2021_09_06_H__
#include <string>
#include <vector>
#include <cassert>

#include "define.h"
#include "define/shader_define.h"
#include "define/event_define.h"
#include "define/math_define.h"
#include "define/glenum_define.h"

typedef unsigned int  uint;
typedef unsigned char uint8;
typedef unsigned char byte;
typedef unsigned int  GL_HANDLE;

#define DEFINE_XSTR(s) DEFINE_STR(s)
#define DEFINE_STR(s) #s

#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

#define GL_ERROR_MSG_SIZE 512  //openGL ������Ϣ��־buff size

#define PI 3.14159265359

#if CC_DISABLE_ASSET
	#define CC_ASSERT( cond )
	#define ASSERT(cond, fmt, ...)
#else
	#define CC_ASSERT( cond ) assert((cond))
	#define ASSERT( cond, fmt, ...)  if(!(cond)){ fprintf(stderr, fmt, ##__VA_ARGS__); assert(false); };
#endif

#define PLAT_WIN		1
#define PLAT_ANDROID	2
#define PLAT_IOS		3
#define PLAT_MAC		4


#ifdef __APPLE__
	#define CUR_PLAT		PLAT_MAC
#else
	#define CUR_PLAT		PLAT_WIN
#endif

#define CREATE_FUNC( CLS_NAME ) \
	static CLS_NAME* create(){ \
		CLS_NAME* obj = new CLS_NAME(); \
		if(obj) \
			obj->doLoad(); \
		return obj; \
	}

#define CCLOG( format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOGERROR( format, ...) fprintf(stderr, format, ##__VA_ARGS__ )


#define BEGIN_NAMESPACE  namespace OGS_OLD{
#define END_NAMESPACE }

#define USING_NAMESPACE using namespace OGS_OLD


#define BEGIN_OGS_NAMESPACE  namespace OGS{
#define END_OGS_NAMESPACE }
#define USING_OGS_NAMESPACE using namespace OGS

#define SAFE_DELTE( ptr ) do{ if((ptr) != nullptr){ delete (ptr);} } while(false)

#endif//__COMMON_2021_09_06_H__