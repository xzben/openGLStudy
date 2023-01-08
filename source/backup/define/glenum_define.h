#ifndef __2022_04_06_GL_ENUM_DEFINE_H__
#define __2022_04_06_GL_ENUM_DEFINE_H__

#include "glad/glad.h"

enum class DepthFunc
{
	ALWAYS = GL_ALWAYS,  //永远通过测试
	NEVER = GL_NEVER,    //永远不通过测试
	LESS = GL_LESS,      // 片段深度值小于缓冲深度值时通过
	EQUAL = GL_EQUAL,    // 片段深度值等于缓冲深度值时通过
	LEQUAL = GL_LEQUAL,  // 片段深度值小于等于缓冲深度值时通过
	GREATER = GL_GREATER,  //片段深度值大于缓冲深度值时通过
	NOTEQUAL = GL_NOTEQUAL,//片段深度值不等于缓冲深度值时通过
	GEQUAL = GL_GEQUAL,//片段深度值大于等于缓冲深度值通过
};

enum class StencilFunc
{
	ALWAYS = GL_ALWAYS,
	NEVER = GL_NEVER,
	LESS = GL_LESS,
	LEQUAL = GL_LEQUAL,
	GREATER = GL_GREATER,
	GEQUAL = GL_GEQUAL,
	EQUAL = GL_EQUAL,
	NOTEQUAL = GL_NOTEQUAL,
};

enum class StencilOp
{
	KEEP = GL_KEEP,   //保持当前储存的模板值
	ZERO = GL_ZERO,   //将模板值设置为0
	REPLACE = GL_REPLACE, //将模板值设置为 glStencilFunc 函数设置的 ref 值
	INCR = GL_INCR, // 模板值 小于最大值则模板值加1
	INCR_WRAP = GL_INCR_WRAP, //与 GL_INCR 一样，只是如果超过最大值则归零
	DECR = GL_DECR, //模板值大于最小值则减1
	DECR_WRAP = GL_DECR_WRAP,//模板值如果大于最小值则减一，否则就设置为最大值
	INVERT = GL_INVERT, //按位翻转当前模板缓冲值
};

enum class BlendFunc
{
	ZERO = GL_ZERO, // 因子等于0
	ONE = GL_ONE,   // 因子等于1
	SRC_COLOR = GL_SRC_COLOR,  // 因子等于源颜色向量C¯source
	ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR, //因子等于1−C¯source
	DST_COLOR = GL_DST_COLOR, //因子等于目标颜色向量C¯destination
	ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR, //因子等于1−C¯destination
	SRC_ALPHA = GL_SRC_ALPHA, //因子等于C¯source的alpha分量
	ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA, //因子等于1− C¯source的alpha分量
	DST_ALPHA = GL_DST_ALPHA, //因子等于C¯destination的alpha分量
	ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA, //因子等于1− C¯destination的alpha分量
	CONSTANT_COLOR = GL_CONSTANT_COLOR, //因子等于常数颜色向量C¯constant
	ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR, //因子等于1−C¯constant
	CONSTANT_ALPHA = GL_CONSTANT_ALPHA, //因子等于C¯constant的alpha分量
	ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA, // 因子等于1− C¯constant的alpha分量
};

enum class CullFace
{
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONT_AND_BACK = GL_FRONT_AND_BACK,
};

enum class FrontFace
{
	CCW = GL_CCW, //逆时针环绕
	CW = GL_CW, //顺时针环绕
};


GLenum glCheckError_(const char* file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif//__2022_04_06_GL_ENUM_DEFINE_H__