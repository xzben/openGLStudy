#ifndef __2022_01_04_RENDER_CONFIG_H__
#define __2022_01_04_RENDER_CONFIG_H__


typedef unsigned int VAO_HANDLE;
typedef unsigned int VBO_HANDLE;
typedef unsigned int EBO_HANDLE;
typedef unsigned int TEXTURE_HANDLE;

enum MESH_DESC_BIT
{
	VER = 1<<0,
	COLOR = 1<<1,
	UV = 1<<2,
};

enum class MESH_DESC
{
	VERTICLE = MESH_DESC_BIT::VER,
	VERTICLE_COLOR = MESH_DESC_BIT::VER | MESH_DESC_BIT::COLOR,
	VERTICLE_COLOR_UV = MESH_DESC_BIT::VER | MESH_DESC_BIT::COLOR | MESH_DESC_BIT::UV,
};

enum class IMAGE_TYPE {
	PNG,
	JPEG,
	TGA,
	UNKNOW,
};

enum class TEXTURE_WRAP 
{
	REPEAT,   //�ظ�
	MIRRORED_REPEAT, //�����ظ�
	CLAMP_TO_EDGE,  // ��Ե�ظ�
	CLAMP_TO_BORDER, //����ʹ��ָ����Ե��ɫ
};

enum class TEXTURE_FILTER
{
	NEAREST, //�ٽ�����  ѡ�����ĵ���ӽ�����������Ǹ�����
	LINEAR, // ���Թ���  ��������������긽�����������أ������һ����ֵ�����Ƴ���Щ��������֮�����ɫ
	NEAREST_MIPMAP_NEAREST,  // ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
	LINEAR_MIPMAP_NEAREST,   // ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
	NEAREST_MIPMAP_LINEAR,	// ��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
	LINEAR_MIPMAP_LINEAR,   // �������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
};

#endif//__2022_01_04_RENDER_CONFIG_H__