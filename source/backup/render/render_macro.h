#pragma once

#include "common.h"
#include "core/math/math.h"
BEGIN_OGS_NAMESPACE

using RenderHandle = unsigned int;

const RenderHandle INVALID_HANDLE = 0;

enum class TextureWrap : unsigned char
{
	REPEAT,  //重复纹理图像
	MIRRORED_REPEAT, //REPEAT一样，但每次重复图片是镜像放置的。
	CLAMP_TO_EDGE, //纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	CLAMP_TO_BORDER, //超出的坐标为用户指定的边缘颜色。
};

enum class ValueType
{
	UNKNOWN,
	BOOL,
	BOOL2,
	BOOL3,
	BOOL4,
	INT,
	INT2,
	INT3,
	INT4,
	UINT,
	UINT2,
	UINT3,
	UINT4,
	FLOAT,
	FLOAT2,
	FLOAT3,
	FLOAT4,
	MAT2,
	MAT2X3,
	MAT2X4,
	MAT3X2,
	MAT3,
	MAT3X4,
	MAT4X2,
	MAT4X3,
	MAT4,
	// combined image samplers
	SAMPLER1D,
	SAMPLER1D_ARRAY,
	SAMPLER2D,
	SAMPLER2D_ARRAY,
	SAMPLER3D,
	SAMPLER_CUBE,
	// sampler
	SAMPLER,
	// sampled textures
	TEXTURE1D,
	TEXTURE1D_ARRAY,
	TEXTURE2D,
	TEXTURE2D_ARRAY,
	TEXTURE3D,
	TEXTURE_CUBE,
	// storage images
	IMAGE1D,
	IMAGE1D_ARRAY,
	IMAGE2D,
	IMAGE2D_ARRAY,
	IMAGE3D,
	IMAGE_CUBE,
	// input attachment
	SUBPASS_INPUT,
	COUNT,
};

enum class PrimitiveMode
{
	POINT_LIST,
	LINE_LIST,
	LINE_STRIP,
	LINE_LOOP,
	LINE_LIST_ADJACENCY,
	LINE_STRIP_ADJACENCY,
	ISO_LINE_LIST,
	// raycast detectable:
	TRIANGLE_LIST,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	TRIANGLE_LIST_ADJACENCY,
	TRIANGLE_STRIP_ADJACENCY,
	TRIANGLE_PATCH_ADJACENCY,
	QUAD_PATCH_LIST,
};

enum class PolygonMode
{
	FILL,
	POINT,
	LINE,
};

enum class TextureFormat
{
	Unknow,
	R8,
	G8,
	B8,
	A8,
	RG8,
	RGB8,
	RGBA8,
};
enum class TextureSampleType
{
	DIFFUSE,
	SPECULAR,
	AMBIENT,
	HEIGHT,
	NORMAL,
};

enum class TextureFilter : unsigned char
{
	NEAREST,
	LINEAR,
	NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR,
};

enum class ClearType : unsigned char
{
	CLEAR_NONE = 0,
	CLEAR_COLOR = 1,
	CLEAR_DEPTH = 2,
	CLEAR_STENCIL = 4,
	CLEAR_ALL = CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL,
};

enum class AttachmentType
{
	COLOR_ATTACHMENT,
	DEPTH_24_STENCIL8_ATTACHMENT,
};

struct SampleInfo
{
	static SampleInfo DefaultTexture;
	static SampleInfo DefaultColorAttachment;
	static SampleInfo DefaultDepthStencilAttachment;

	TextureWrap wrap = TextureWrap::CLAMP_TO_EDGE;     //纹理环绕方案
	TextureFilter filterMin = TextureFilter::NEAREST;  //缩小时纹理过滤方案
	TextureFilter filterMag = TextureFilter::NEAREST;  //放大时纹理过滤方案

	SampleInfo(){}
	SampleInfo(TextureWrap w, TextureFilter fmin, TextureFilter fmag)
	: wrap(w), filterMin(fmin), filterMag(fmag)
	{
	}

	SampleInfo(int value)
	{
		wrap = (TextureWrap)(value & 0x3);
		filterMin = TextureFilter((value >> 2) & 0x7);
		filterMag = TextureFilter((value >> 5) & 0x7);

	}

	int GetSampeValue()
	{
		int value = (0x3&(int)wrap) | (((int)filterMin&0x7) << 2) | ((int)filterMag&0x7) << 5 ;

		return value;
	}
};


enum class MeshDataFmt
{
	POS,
	POS_UV,
	POS_COLOR_UV,
	POS_COLOR_NORMAL_UV,
	POS_COLOR_NORMA_TANGENT_UV,
};

struct MeshDataDesc
{
	MeshDataFmt type;
	int size;
};

enum class CameraProjection
{
	ORTHO,
	PERSPECTIVE,
};

enum class LightType
{
	Direction,
	Point,
	Spot,
};


enum class VertexFmt
{
	POS = 1 << 0,  //位置
	COLOR = 1 << 1, //颜色
	TEXCOORD = 1 << 2, //纹理坐标
	NORMAL = 1 << 3, //法线
	TANGENT = 1 << 4, //切线
	BITANGENT = 1 << 5, // 副切线/副法线

	POS_NORMAL = POS | NORMAL,
	POS_TEXCOORD = POS | TEXCOORD,
	POS_COLOR_TEXCOORD = POS | COLOR | TEXCOORD,
	POS_COLOR_TEXCOORD_NORMAL = POS | COLOR | TEXCOORD | NORMAL,
	POS_COLOR_NOMAL = POS | COLOR | NORMAL,
};

enum class AttributeName
{
	ATTR_UNKNOWN = -1,
	ATTR_POSITION,
	ATTR_NORMAL,
	ATTR_TANGENT,
	ATTR_BITANGENT,
	ATTR_WEIGHTS,
	ATTR_JOINTS,
	ATTR_COLOR,
	ATTR_COLOR1,
	ATTR_COLOR2,
	ATTR_TEX_COORD,
	ATTR_TEX_COORD1,
	ATTR_TEX_COORD2,
	ATTR_TEX_COORD3,
	ATTR_TEX_COORD4,
	ATTR_TEX_COORD5,
	ATTR_TEX_COORD6,
	ATTR_TEX_COORD7,
	ATTR_TEX_COORD8,
	ATTR_BATCH_ID,
	ATTR_BATCH_UV,
	ATTR_COUNT,
};

enum class ComparisonFunc 
{
	NEVER,
	LESS,
	EQUAL,
	LESS_EQUAL,
	GREATER,
	NOT_EQUAL,
	GREATER_EQUAL,
	ALWAYS,
};

enum class StencilOp 
{
	ZERO,
	KEEP,
	REPLACE,
	INCR,
	DECR,
	INVERT,
	INCR_WRAP,
	DECR_WRAP,
};

enum class BlendFactor 
{
	ZERO,
	ONE,
	SRC_ALPHA,
	DST_ALPHA,
	ONE_MINUS_SRC_ALPHA,
	ONE_MINUS_DST_ALPHA,
	SRC_COLOR,
	DST_COLOR,
	ONE_MINUS_SRC_COLOR,
	ONE_MINUS_DST_COLOR,
	SRC_ALPHA_SATURATE,
	CONSTANT_COLOR,
	ONE_MINUS_CONSTANT_COLOR,
	CONSTANT_ALPHA,
	ONE_MINUS_CONSTANT_ALPHA,
};

enum class BlendOp 
{
	ADD,
	SUB,
	REV_SUB,
	MIN,
	MAX,
};

enum class ColorMask {
	NONE = 0x0,
	R = 0x1,
	G = 0x2,
	B = 0x4,
	A = 0x8,
	ALL = R | G | B | A,
};

enum class CullMode
{
	NONE,
	FRONT,
	BACK,
};

enum class DynamicStateFlagBit 
{
	NONE = 0x0,
	LINE_WIDTH = 0x1,
	DEPTH_BIAS = 0x2,
	BLEND_CONSTANTS = 0x4,
	DEPTH_BOUNDS = 0x8,
	STENCIL_WRITE_MASK = 0x10,
	STENCIL_COMPARE_MASK = 0x20,
};

enum class StencilFace {
	FRONT = 0x1,
	BACK = 0x2,
	ALL = 0x3,
};


enum class ClearFlagBit {
	NONE = 0,
	COLOR = 0x1,
	DEPTH = 0x2,
	STENCIL = 0x4,
	DEPTH_STENCIL = DEPTH | STENCIL,
	ALL = COLOR | DEPTH | STENCIL,
};

class Attribute
{
public:
	AttributeName name{ AttributeName::ATTR_UNKNOWN };
	bool		isNormalized{ false };
	bool		isInstanced{ false };
	uint16		location{ 0 };
	Attribute(AttributeName n):name(n){}
	Attribute(const Attribute& rhs)
	{
		name = rhs.name;
		isNormalized = rhs.isNormalized;
		isInstanced = rhs.isInstanced;
		location = rhs.location;
	}
};

class Uniform
{
public:
	std::string name{ "" };
	ValueType    type{ ValueType::UNKNOWN };
	uint16       count;
};

class UniformBlock
{
	std::string name{ "" };
	std::vector<Uniform> members;
};


struct ShaderMacro
{
public:
	enum ValueType {
		STRING,
		BOOL,
		NUMBER,
	};

	ShaderMacro(std::string& n, std::string& value)
		:name(n)
	{
		type = STRING;
		strValue = value;
	}

	ShaderMacro(std::string& n, bool value)
		:name(n)
	{
		type = BOOL;
		boolValue = value;
	}

	ShaderMacro(std::string& n, int32 value)
		:name(n)
	{
		type = NUMBER;
		intValue = value;
	}

	~ShaderMacro()
	{

	}

	std::string name;
	ValueType   type;

	union{
		std::string strValue;
		bool		boolValue;
		int32		intValue;
	};

};

struct MaterialProperty
{
public:
	std::string name;
	ValueType   type;
	
	union{
		bool boolVal;
		bool boolArr2[2];
		bool boolArr3[3];
		bool boolArr4[4];

		int  intValue;
		int  intArr2[2];
		int  intArr3[3];
		int  intArr4[4];

		uint32 uintValue;
		uint32 uintArr2[2];
		uint32 uintArr3[3];
		uint32 uintArr4[4];

		float  floatValue;
		float  floatArr2[2];
		float  floatArr3[3];
		float  floatArr4[4];

		float matrix3x3[9];
		float matrix4x4[16];
	};
};

enum class RenderPassStage
{
	DEFAULT = 100,
	UI = 200,
};

//光栅化阶段
struct RasterizerState
{
public:
	bool isDiscard;
	PolygonMode polygonModel;
	CullMode cullMode;
	bool isFrontFaceCCW; //是否顺时针是正面
	bool depthDiasEnable;
	int depthBias;
	int depthDiasClamp;
	int depthDiasSlop;
	bool isDepthClip;
	bool isMultisampel;
	uint16 lineWidth;
};

struct BlendTarget
{
public:
	bool blend;
	BlendFactor blendSrc{ BlendFactor::ONE };
	BlendFactor blendDst{ BlendFactor::ZERO };
	BlendOp     blendEq{ BlendOp::ADD };
	BlendFactor blendSrcAlpha{ BlendFactor::ONE };
	BlendFactor blendDstAplha{ BlendFactor::ZERO };
	BlendOp     blendAlphaEq{ BlendOp::ADD };
	ColorMask	blendColorMask{ ColorMask::ALL };
};

struct BlendState
{
public:
	bool isA2C;
	bool isIndepend;
	Color blendColor;
	std::vector<BlendTarget> targets;
};

struct DepthStencilState
{
public:
	bool depthTest;
	bool depthWrite;
	ComparisonFunc depthFunc{ ComparisonFunc::LESS };

	bool stencilTestFront;
	ComparisonFunc stencilFuncFront{ComparisonFunc::ALWAYS};
	uint16 stencilReadMaskFront{ 0xffff };
	uint16 stencilWriteMaskFront{ 0xffff };
	StencilOp stencilFailOpFront{ StencilOp::KEEP };
	StencilOp stencilZFailOpFront{ StencilOp::KEEP };
	StencilOp stencilPassOpFront{ StencilOp::KEEP };
	uint16 stencilRefFront{ 1 };
	bool  stencilTestBack{ false };

	ComparisonFunc stencilFuncBack{ ComparisonFunc::ALWAYS };
	uint16 stencilReadMaskBack{ 0xffff };
	uint16 stencilWriteMaskBack{ 0xffff };
	StencilOp stencilFailOpBack{ StencilOp::KEEP };
	StencilOp stencilZFailOpBack{ StencilOp::KEEP };
	StencilOp stencilPassOpBack{ StencilOp::KEEP };
	uint16 stencilRefBack{ 1 };
};

struct IPassStates
{
public:
	int priority;
	PrimitiveMode primitive;
	RenderPassStage stage;
	RasterizerState rasterizerState;
	DepthStencilState depthStencilState;
	BlendState blendState;
	DynamicStateFlagBit dynamicStates;
	std::string phase;
};

END_OGS_NAMESPACE