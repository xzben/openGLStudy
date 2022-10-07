#ifndef __2022_01_06_DEFINE_H__
#define __2022_01_06_DEFINE_H__

#include <cassert>
#include <cstdio>
#include <string>

#define RENDER_OPENGL2	 0
#define RENDER_OPENGL3   1
#define RENDER_VULKAN	 2
#define RENDER_DX12		 3

#define RENDER_PLAT RENDER_OPENGL3

enum class ResolutionFit
{
	FIXED_WIDTH,  //固定宽度
	FIXED_HEIGHT, //固定高度
	AUTO_FIT,		  //自动根据宽度和高度比例与设计分辨率宽高比，自动选择适配高度或者宽度，保证满足设计分辨率
};

struct WindowCreateInfo
{
	int         width{ 1280 };
	int         height{ 720 };
	const char* title{ "OpenGLStudy" };
	bool		maximized{ true }; //是否最大化
	bool        is_fullscreen{ false };
};

enum class CameraType {
	Frustum,   //平截头
	Perspective, //透视
};

enum class GroupMask : unsigned int{
	EMPTY = 0x00000000,  //不属于任何分组
	UI = 0x00000001,  //UI 分组
	D3 = 0x00000002,  // 3D 对象分组
	DEFAULT = 0xffffffff, // 默认全部都
};

#define DELETE_OBJ( pointer ) do{ if(pointer != nullptr) delete pointer; pointer = nullptr; }while(false)
#define DELETE_ARRAY_OBJ( pointer ) do{ if(pointer != nullptr) delete[] pointer; pointer = nullptr; }while(false)

#define SAFE_DEL_REF( pointer ) do{ if(pointer != nullptr) pointer->delRef(); pointer = nullptr; } while(false)
#define SAFE_ADD_REF( pointer  ) do{ if(pointer != nullptr) pointer->addRef(); } while(false)

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_EPSILON                0.000001f


typedef unsigned int  uint32;
typedef long long	  int64;
typedef unsigned long long uint64;
typedef int			  int32;
typedef unsigned int  uint;
typedef unsigned char uint8;
typedef unsigned char byte;
typedef unsigned int  GL_HANDLE;
typedef std::conditional_t<sizeof(void*) == 4, int32, int64> ptrsize;

#define DEFINE_XSTR(s) DEFINE_STR(s)
#define DEFINE_STR(s) #s

#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

#define GL_ERROR_MSG_SIZE 512  //openGL 错误信息日志buff size

#define PI 3.14159265359

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


#define BEGIN_NAMESPACE  namespace OGS_OLD{
#define END_NAMESPACE }

#define USING_NAMESPACE using namespace OGS_OLD


#define BEGIN_OGS_NAMESPACE  namespace OGS{
#define END_OGS_NAMESPACE }
#define USING_OGS_NAMESPACE using namespace OGS

#define SAFE_DELTE( ptr ) do{ if((ptr) != nullptr){ delete (ptr);} ptr = nullptr; } while(false)

#if CC_DISABLE_ASSET
#define CC_ASSERT( cond )
#define ASSERT(cond, fmt, ...)
#else
#define CC_ASSERT( cond ) assert((cond))
#define ASSERT( cond, fmt, ...)  if(!(cond)){ fprintf(stderr, fmt, ##__VA_ARGS__); assert(false); };
#endif

#endif//__2022_01_06_DEFINE_H__