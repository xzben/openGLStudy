#ifndef __2022_03_16_SHADER_DEFINE_H__
#define __2022_03_16_SHADER_DEFINE_H__

//���ڱ�ʶ�������ݳ�Ա
enum class VerticleMember
{
	POS = 1 << 0,
	COLOR = 1 << 1,
	TEXCOORD = 1 << 2,
	NORMAL = 1 << 3,

	POS_NORMAL = POS | NORMAL,
	POS_COLOR_TEXCOORD = POS | COLOR | TEXCOORD,
	POS_COLOR_TEXCOORD_NORMAL = POS | COLOR | TEXCOORD | NORMAL,
};

#define SHADER_POS_NAME		"aPos"
#define SHADER_POS_INDEX	0

#define SHADER_COLOR_NAME	"aColor"
#define SHADER_COLOR_INDEX	1

#define SHADER_TEXCOORD_NAME "aTexCoord"
#define SHADER_TEXCOORD_INDEX 2

#define SHADER_NORMAL_NAME "aNormal"
#define SHADER_NORMAL_INDEX 3

#define SHADER_MAIN_TEXTURE_INDEX 0
#define SHADER_MAIN_TEXTURE_NAME "mainTexture"

#define SHADER_COMMON_UNIFORM_MVP  "cc_mvp"			// mat4 
#define SHADER_COMMON_UNIFORM_MODEL "cc_model"		// mat4
#define SHADER_COMMON_UNIFORM_VIEW "cc_view"		// mat4
#define SHADER_COMMON_UNIFORM_PROJECTION "cc_projection"		// mat4

#define SHADER_COMMON_UNIFORM_TIMER "cc_timer"		// fvec3  x == ��ǰ�ۼ�ʱ�� y == ��ǰ dt ʱ��

#define SHADER_UNIFORM_COLOR "uColor"  //ÿ���ڵ㶼������һ����ɫֵ�� ������ɫֵ�ǲ�ͬ�ģ����color�ǹ��������������ж����ϵ���ɫ�仯


#define SHADER_LIGHT_POS				"light.pos"
#define SHADER_LIGHT_AMBIENT_COLOR		"light.ambient"
#define SHADER_LIGHT_DIFFUSE_COLOR		"light.diffuse"
#define SHADER_LIGHT_SPECULAR_COLOR		"light.specular"
#define SHADER_LIGHT_STRENGTH			"light.strength"

#define SHADER_CAMERA_POS				"cameraPos"

#endif//__2022_03_16_SHADER_DEFINE_H__
