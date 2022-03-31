#ifndef __2022_03_22_RENDER_COLOR_H__
#define __2022_03_22_RENDER_COLOR_H__

#include "common.h"
BEGIN_NAMESPACE

class Color;

class RGB
{
public:
	union
	{
		float values[3];
		struct {
			float r, g, b;
		};
	};

	RGB()
		:RGB(1.0f, 1.0f, 1.0f)
	{}

	RGB(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	RGB(uint8 r, uint8 g, uint8 b)
		:RGB(r / 255.0f, g / 255.0f, b / 255.0f)
	{}


	RGB operator*(const RGB& rvalue)
	{
		RGB result;
		result.r = r * rvalue.r;
		result.g = g * rvalue.g;
		result.b = b * rvalue.b;


		return result;
	}

	void operator*=(const RGB& rvalue)
	{
		r *= rvalue.r;
		g *= rvalue.g;
		b *= rvalue.b;
	}

	RGB operator*(const float value)
	{
		RGB result;
		result.r = r * value;
		result.g = g * value;
		result.b = b * value;


		return result;
	}

	void operator*=(const float value)
	{
		r *= value;
		g *= value;
		b *= value;
	}
};


class Color
{
public:
	union
	{
		float values[4];
		struct{
			float r, g, b, a;
		};
	};
	
	Color()
		:Color(1.0f, 1.0f, 1.0f, 1.0f)
	{}

	Color(const RGB& rgb)
		: Color(rgb.r, rgb.g, rgb.b, 1.0f)
	{

	}

	Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b)
		:Color(r, g, b, 1.0)
	{}

	Color(uint8 r, uint8 g, uint8 b, uint8 a)
		:Color(r/255.0f, g/255.0f, b/255.0f, a/255.0f)
	{}
	
	Color operator*(const Color& rvalue)
	{
		Color result;
		result.r = r * rvalue.r;
		result.g = g * rvalue.g;
		result.b = b * rvalue.b;
		result.a = a * rvalue.a;

		return result;
	}

	void operator*=(const Color& rvalue)
	{
		r *= rvalue.r;
		g *= rvalue.g;
		b *= rvalue.b;
		a *= rvalue.a;
	}

	Color operator*(const float& rvalue)
	{
		Color result;
		result.r = r * rvalue;
		result.g = g * rvalue;
		result.b = b * rvalue;
		result.a = a * rvalue;

		return result;
	}

	void operator*=(const float& rvalue)
	{
		r *= rvalue;
		g *= rvalue;
		b *= rvalue;
		a *= rvalue;
	}

	RGB toRGB() const
	{
		return RGB(r, g, b);
	}
};


using RGBA = Color;

END_NAMESPACE
#endif//__2022_03_22_RENDER_COLOR_H__