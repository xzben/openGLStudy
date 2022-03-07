#ifndef __2022_01_06_DEFINE_H__
#define __2022_01_06_DEFINE_H__

enum class ResolutionFit
{
	FIXED_WIDTH,  //固定宽度
	FIXED_HEIGHT, //固定高度
	AUTO_FIT,		  //自动根据宽度和高度比例与设计分辨率宽高比，自动选择适配高度或者宽度，保证满足设计分辨率
};

#endif//__2022_01_06_DEFINE_H__