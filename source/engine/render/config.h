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
	REPEAT,   //重复
	MIRRORED_REPEAT, //镜像重复
	CLAMP_TO_EDGE,  // 边缘重复
	CLAMP_TO_BORDER, //超出使用指定边缘颜色
};

enum class TEXTURE_FILTER
{
	NEAREST, //临近过滤  选择中心点最接近纹理坐标的那个像素
	LINEAR, // 线性过滤  它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色
	NEAREST_MIPMAP_NEAREST,  // 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
	LINEAR_MIPMAP_NEAREST,   // 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
	NEAREST_MIPMAP_LINEAR,	// 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
	LINEAR_MIPMAP_LINEAR,   // 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
};

#endif//__2022_01_04_RENDER_CONFIG_H__