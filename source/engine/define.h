#ifndef __2022_01_06_DEFINE_H__
#define __2022_01_06_DEFINE_H__

enum class ResolutionFit
{
	FIXED_WIDTH,  //固定宽度
	FIXED_HEIGHT, //固定高度
	AUTO_FIT,		  //自动根据宽度和高度比例与设计分辨率宽高比，自动选择适配高度或者宽度，保证满足设计分辨率
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

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_EPSILON                0.000001f

#endif//__2022_01_06_DEFINE_H__