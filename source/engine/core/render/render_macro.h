#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

enum TextureWrap : unsigned char
{
	REPEAT,  //�ظ�����ͼ��
	MIRRORED_REPEAT, //REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	CLAMP_TO_EDGE, //��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	CLAMP_TO_BORDER, //����������Ϊ�û�ָ���ı�Ե��ɫ��
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
	TextureWrap wrap = TextureWrap::CLAMP_TO_EDGE;     //�����Ʒ���
	TextureFilter filterMin = TextureFilter::NEAREST;  //��Сʱ������˷���
	TextureFilter filterMag = TextureFilter::NEAREST;  //�Ŵ�ʱ������˷���

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