#ifndef __2022_03_16_SHADER_DEFINE_H__
#define __2022_03_16_SHADER_DEFINE_H__

#define SHADER_POS_NAME		"aPos"
#define SHADER_POS_INDEX	0

#define SHADER_COLOR_NAME	"aColor"
#define SHADER_COLOR_INDEX	1

#define SHADER_TEXCOORD_NAME "aTexCoord"
#define SHADER_TEXCOORD_INDEX 2

#define SHADER_MAIN_TEXTURE_INDEX 0
#define SHADER_MAIN_TEXTURE_NAME "mainTexture"

#define SHADER_COMMON_UNIFORM_MVP  "cc_mvp"			// mat4 
#define SHADER_COMMON_UNIFORM_MODEL "cc_model"		// mat4
#define SHADER_COMMON_UNIFORM_VIEW "cc_view"		// mat4
#define SHADER_COMMON_UNIFORM_PROJECTION "cc_projection"		// mat4

#define SHADER_COMMON_UNIFORM_TIMER "cc_timer"		// fvec3  x == ��ǰ�ۼ�ʱ�� y == ��ǰ dt ʱ��

#define SHADER_UNIFORM_COLOR "uColor"  //ÿ���ڵ㶼������һ����ɫֵ�� ������ɫֵ�ǲ�ͬ�ģ����color�ǹ��������������ж����ϵ���ɫ�仯

#endif//__2022_03_16_SHADER_DEFINE_H__
