#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

enum TextureWrap : unsigned char
{
	REPEAT,  //重复纹理图像
	MIRRORED_REPEAT, //REPEAT一样，但每次重复图片是镜像放置的。
	CLAMP_TO_EDGE, //纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	CLAMP_TO_BORDER, //超出的坐标为用户指定的边缘颜色。
};

enum TextureFilter : unsigned char
{
	NEAREST,
	LINEAR,
	NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR,
};

struct SampleInfo
{
	TextureWrap wrap = TextureWrap::CLAMP_TO_EDGE;     //纹理环绕方案
	TextureFilter filterMin = TextureFilter::NEAREST;  //缩小时纹理过滤方案
	TextureFilter filterMag = TextureFilter::NEAREST;  //放大时纹理过滤方案

	SampleInfo(int value)
	{
		wrap = (TextureWrap)(value & 0x3);
		filterMin = TextureFilter((value >> 2) & 0x7);
		filterMag = TextureFilter((value >> 5) & 0x7);

	}

	int GetSampeValue()
	{
		int value = (0x3&wrap) | ((filterMin&0x7) << 2) | (filterMag&0x7) << 5 ;

		return value;
	}
};

END_OGS_NAMESPACE