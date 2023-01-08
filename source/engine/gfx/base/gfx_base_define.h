#pragma once

#include "define.h"
#include "core/base/Object.h"
#include <vector>
#include "core/math/Size.h"

BEGIN_OGS_GFX_NAMESPACE

enum class API {
	UNKNOWN,
	GLES2,
	GLES3,
	METAL,
	VULKAN,
	NVN,
	WEBGL,
	WEBGL2,
	WEBGPU,
};

enum class ObjectType {
	UNKNOWN,
	SWAPCHAIN,
	BUFFER,
	TEXTURE,
	RENDER_PASS,
	FRAMEBUFFER,
	SAMPLER,
	SHADER,
	DESCRIPTOR_SET_LAYOUT,
	PIPELINE_LAYOUT,
	PIPELINE_STATE,
	DESCRIPTOR_SET,
	INPUT_ASSEMBLER,
	COMMAND_BUFFER,
	QUEUE,
	QUERY_POOL,
	GLOBAL_BARRIER,
	TEXTURE_BARRIER,
	BUFFER_BARRIER,
	COUNT,
};

enum class Format {

	UNKNOWN,

	A8,
	L8,
	LA8,

	R8,
	R8SN,
	R8UI,
	R8I,
	R16F,
	R16UI,
	R16I,
	R32F,
	R32UI,
	R32I,

	RG8,
	RG8SN,
	RG8UI,
	RG8I,
	RG16F,
	RG16UI,
	RG16I,
	RG32F,
	RG32UI,
	RG32I,

	RGB8,
	SRGB8,
	RGB8SN,
	RGB8UI,
	RGB8I,
	RGB16F,
	RGB16UI,
	RGB16I,
	RGB32F,
	RGB32UI,
	RGB32I,

	RGBA8,
	BGRA8,
	SRGB8_A8,
	RGBA8SN,
	RGBA8UI,
	RGBA8I,
	RGBA16F,
	RGBA16UI,
	RGBA16I,
	RGBA32F,
	RGBA32UI,
	RGBA32I,

	// Special Format
	R5G6B5,
	R11G11B10F,
	RGB5A1,
	RGBA4,
	RGB10A2,
	RGB10A2UI,
	RGB9E5,

	// Depth-Stencil Format
	DEPTH,
	DEPTH_STENCIL,

	// Compressed Format

	// Block Compression Format, DDS (DirectDraw Surface)
	// DXT1: 3 channels (5:6:5), 1/8 original size, with 0 or 1 bit of alpha
	BC1,
	BC1_ALPHA,
	BC1_SRGB,
	BC1_SRGB_ALPHA,
	// DXT3: 4 channels (5:6:5), 1/4 original size, with 4 bits of alpha
	BC2,
	BC2_SRGB,
	// DXT5: 4 channels (5:6:5), 1/4 original size, with 8 bits of alpha
	BC3,
	BC3_SRGB,
	// 1 channel (8), 1/4 original size
	BC4,
	BC4_SNORM,
	// 2 channels (8:8), 1/2 original size
	BC5,
	BC5_SNORM,
	// 3 channels (16:16:16), half-floating point, 1/6 original size
	// UF16: unsigned float, 5 exponent bits + 11 mantissa bits
	// SF16: signed float, 1 signed bit + 5 exponent bits + 10 mantissa bits
	BC6H_UF16,
	BC6H_SF16,
	// 4 channels (4~7 bits per channel) with 0 to 8 bits of alpha, 1/3 original size
	BC7,
	BC7_SRGB,

	// Ericsson Texture Compression Format
	ETC_RGB8,
	ETC2_RGB8,
	ETC2_SRGB8,
	ETC2_RGB8_A1,
	ETC2_SRGB8_A1,
	ETC2_RGBA8,
	ETC2_SRGB8_A8,
	EAC_R11,
	EAC_R11SN,
	EAC_RG11,
	EAC_RG11SN,

	// PVRTC (PowerVR)
	PVRTC_RGB2,
	PVRTC_RGBA2,
	PVRTC_RGB4,
	PVRTC_RGBA4,
	PVRTC2_2BPP,
	PVRTC2_4BPP,

	// ASTC (Adaptive Scalable Texture Compression)
	ASTC_RGBA_4X4,
	ASTC_RGBA_5X4,
	ASTC_RGBA_5X5,
	ASTC_RGBA_6X5,
	ASTC_RGBA_6X6,
	ASTC_RGBA_8X5,
	ASTC_RGBA_8X6,
	ASTC_RGBA_8X8,
	ASTC_RGBA_10X5,
	ASTC_RGBA_10X6,
	ASTC_RGBA_10X8,
	ASTC_RGBA_10X10,
	ASTC_RGBA_12X10,
	ASTC_RGBA_12X12,

	// ASTC (Adaptive Scalable Texture Compression) SRGB
	ASTC_SRGBA_4X4,
	ASTC_SRGBA_5X4,
	ASTC_SRGBA_5X5,
	ASTC_SRGBA_6X5,
	ASTC_SRGBA_6X6,
	ASTC_SRGBA_8X5,
	ASTC_SRGBA_8X6,
	ASTC_SRGBA_8X8,
	ASTC_SRGBA_10X5,
	ASTC_SRGBA_10X6,
	ASTC_SRGBA_10X8,
	ASTC_SRGBA_10X10,
	ASTC_SRGBA_12X10,
	ASTC_SRGBA_12X12,

	// Total count
	COUNT,
};

enum class MemoryAccessBit {
	NONE = 0,
	READ_ONLY = 0x1,
	WRITE_ONLY = 0x2,
	READ_WRITE = READ_ONLY | WRITE_ONLY,
};

enum class FormatType {
	NONE,
	UNORM,
	SNORM,
	UINT,
	INT,
	UFLOAT,
	FLOAT,
};

enum class Type {
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

enum class BufferUsageBit {
	NONE = 0,
	TRANSFER_SRC = 0x1,
	TRANSFER_DST = 0x2,
	INDEX = 0x4,
	VERTEX = 0x8,
	UNIFORM = 0x10,
	STORAGE = 0x20,
	INDIRECT = 0x40,
};

enum class MemoryUsageBit {
	NONE = 0,
	DEVICE = 0x1, // for rarely-updated resources, use MemoryUsageBit::DEVICE
	HOST = 0x2,   // for frequently-updated resources, use MemoryUsageBit::DEVICE | MemoryUsageBit::HOST
};

enum class BufferFlagBit {
	NONE = 0,
};
enum class TextureType
{
	TEX1D,
	TEX2D,
	TEX3D,
	CUBE,
	TEX1D_ARRAY,
	TEX2D_ARRAY,
};

enum class TextureUsageBit {
	NONE = 0,
	TRANSFER_SRC = 0x1,
	TRANSFER_DST = 0x2,
	SAMPLED = 0x4,
	STORAGE = 0x8,
	COLOR_ATTACHMENT = 0x10,
	DEPTH_STENCIL_ATTACHMENT = 0x20,
	INPUT_ATTACHMENT = 0x40,
};

enum class TextureFlagBit {
	NONE = 0,
	GEN_MIPMAP = 0x1,     // Generate mipmaps using bilinear filter
	GENERAL_LAYOUT = 0x2, // For inout framebuffer attachments
};

enum class SampleCount {
	ONE,                  // Single sample
	MULTIPLE_PERFORMANCE, // Multiple samples prioritizing performance over quality
	MULTIPLE_BALANCE,     // Multiple samples leveraging both quality and performance
	MULTIPLE_QUALITY,     // Multiple samples prioritizing quality over performance
};

enum class CommandBufferType {
	PRIMARY,
	SECONDARY,
};

enum class QueueType {
	GRAPHICS,
	COMPUTE,
	TRANSFER,
};

enum class ShaderStageFlagBit {
	NONE = 0x0,
	VERTEX = 0x1,
	CONTROL = 0x2,
	EVALUATION = 0x4,
	GEOMETRY = 0x8,
	FRAGMENT = 0x10,
	COMPUTE = 0x20,
	ALL = 0x3f,
};

enum class SurfaceTransform{
	IDENTITY,
	ROTATE_90,
	ROTATE_180,
	ROTATE_270,
};

enum class LoadOp {
	LOAD,    // Load the previous content from memory
	CLEAR,   // Clear the content to a fixed value
	DISCARD, // Discard the previous content
};

enum class StoreOp {
	STORE,   // Store the pending content to memory
	DISCARD, // Discard the pending content
};

enum class ResolveMode {
	NONE,
	SAMPLE_ZERO,
	AVERAGE,
	MIN,
	MAX,
};

enum Feature {
	ELEMENT_INDEX_UINT,
	INSTANCED_ARRAYS,
	MULTIPLE_RENDER_TARGETS,
	BLEND_MINMAX,
	COMPUTE_SHADER,
	// This flag indicates whether the device can benefit from subpass-style usages.
	// Specifically, this only differs on the GLES backends: the Framebuffer Fetch
	// extension is used to simulate input attachments, so the flag is not set when
	// the extension is not supported, and you should switch to the fallback branch
	// (without the extension requirement) in GLSL shader sources accordingly.
	// Everything else can remain the same.
	//
	// Another caveat when using the Framebuffer Fetch extensions in shaders is that
	// for subpasses with exactly 4 inout attachments the output is automatically set
	// to the last attachment (taking advantage of 'inout' property), and a separate
	// blit operation (if needed) will be added for you afterwards to transfer the
	// rendering result to the correct subpass output texture. This is to ameliorate
	// the max number of attachment limit(4) situation for many devices, and shader
	// sources inside this kind of subpass must match this behavior.
	INPUT_ATTACHMENT_BENEFIT,
	COUNT,
};

enum class FormatFeatureBit {
	NONE = 0,
	RENDER_TARGET = 0x1,     // Allow usages as render pass attachments
	SAMPLED_TEXTURE = 0x2,   // Allow sampled reads in shaders
	LINEAR_FILTER = 0x4,     // Allow linear filtering when sampling in shaders or blitting
	STORAGE_TEXTURE = 0x8,   // Allow storage reads & writes in shaders
	VERTEX_ATTRIBUTE = 0x10, // Allow usages as vertex input attributes
};

enum class DescriptorType {
	UNKNOWN = 0,
	UNIFORM_BUFFER = 0x1,
	DYNAMIC_UNIFORM_BUFFER = 0x2,
	STORAGE_BUFFER = 0x4,
	DYNAMIC_STORAGE_BUFFER = 0x8,
	SAMPLER_TEXTURE = 0x10,
	SAMPLER = 0x20,
	TEXTURE = 0x40,
	STORAGE_IMAGE = 0x80,
	INPUT_ATTACHMENT = 0x100,
};

enum class PolygonMode
{
	FILL,
	POINT,
	LINE,
};

enum class CullMode
{
	NONE,
	FRONT,
	BACK,
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

enum class PipelineBindPoint {
	GRAPHICS,
	COMPUTE,
	RAY_TRACING,
};

class SubpassInfo : public Object
{
public:
	std::vector<int32>	inputs;
	std::vector<int32>  colors;
	std::vector<int32>  resolves;
	std::vector<int32>  preserves;
	int32				depthStencil = -1;
	int32				depthStencilResolve= -1;
	ResolveMode			depthResolveMode{ResolveMode::NONE};
	ResolveMode			stencilResolveMode{ ResolveMode::NONE };
};

struct MemoryStatus
{
public:
	uint32 bufferSize;
	uint32 textureSize;
};

struct DeviceCaps
{
public:
	int32 maxVertexAttributes{0};
	int32 maxVertexUniformVectors{ 0 };
	int32 maxFragmentUniformVectors{ 0 };
	int32 maxTextureUnits{ 0 };
	int32 maxImageUnits{ 0 };
	int32 maxVertexTextureUnits{ 0 };
	int32 maxColorRenderTargets{ 0 };
	int32 maxShaderStorageBufferBindings{ 0 };
	int32 maxShaderStorageBlockSize{ 0 };
	int32 maxUniformBufferBindings{ 0 };
	int32 maxUniformBlockSize{ 0 };
	int32 maxTextureSize{ 0 };
	int32 maxCubeMapTextureSize{ 0 };
	int32 uboOffsetAlignment{ 0 };
	int32 maxComputeSharedMemorySize{ 0 };
	int32 maxComputeWorkGroupInvocations{ 0 };
	Size maxComputeWorkGroupSize{0,0};
	Size maxComputeWorkGroupCount{0,0};
	bool supportQuery = false;
	int32 clipSpaceMinZ{ -1 };
	int32 screenSpaceSignY{ 1 };
	int32 clipSpaceSignY{ 1 };
};

struct BindingMappingInfo
{
public:
	std::vector<int32> maxBlockCounts;
	std::vector<int32> maxSamplerTextureCounts;
	std::vector<int32> maxSamplerCounts;
	std::vector<int32> maxTextureCounts;
	std::vector<int32> maxBufferCounts;
	std::vector<int32> maxImageCounts;
	std::vector<int32> maxSubpassInputCounts;
	std::vector<int32> setIndices;
};

enum class VsyncMode {
	// The application does not synchronizes with the vertical sync.
	// If application renders faster than the display refreshes, frames are wasted and tearing may be observed.
	// FPS is uncapped. Maximum power consumption. If unsupported, "ON" value will be used instead. Minimum latency.
	OFF,
	// The application is always synchronized with the vertical sync. Tearing does not happen.
	// FPS is capped to the display's refresh rate. For fast applications, battery life is improved. Always supported.
	ON,
	// The application synchronizes with the vertical sync, but only if the application rendering speed is greater than refresh rate.
	// Compared to OFF, there is no tearing. Compared to ON, the FPS will be improved for "slower" applications.
	// If unsupported, "ON" value will be used instead. Recommended for most applications. Default if supported.
	RELAXED,
	// The presentation engine will always use the latest fully rendered image.
	// Compared to OFF, no tearing will be observed.
	// Compared to ON, battery power will be worse, especially for faster applications.
	// If unsupported,  "OFF" will be attempted next.
	MAILBOX,
	// The application is capped to using half the vertical sync time.
	// FPS artificially capped to Half the display speed (usually 30fps) to maintain battery.
	// Best possible battery savings. Worst possible performance.
	// Recommended for specific applications where battery saving is critical.
	HALF,
};


enum class Filter {
	NONE,
	POINT,
	LINEAR,
	ANISOTROPIC,
};

enum class Address {
	WRAP,
	MIRROR,
	CLAMP,
	BORDER,
};

class SamplerInfo
{
public:
	Filter minFilter{Filter::LINEAR};
	Filter magFilter{ Filter::LINEAR };
	Filter mipFilter{ Filter::NONE };
	Address addressU{Address::WRAP};
	Address addressV{ Address::WRAP };
	Address addressW{ Address::WRAP };
	uint32  maxAnisotropy{ 0 };
	ComparisonFunc cmpFunc{ ComparisonFunc::ALWAYS };
	SamplerInfo() = default;

	SamplerInfo(const SamplerInfo& info)
	{
		minFilter = info.minFilter;
		magFilter = info.magFilter;
		mipFilter = info.mipFilter;
		addressU = info.addressU;
		addressV = info.addressV;
		addressW = info.addressW;
		maxAnisotropy = info.maxAnisotropy;
		cmpFunc = info.cmpFunc;
	}

	void copy(const SamplerInfo& info)
	{
		*this = info;
	}
};


enum class AccessFlagBit
{
	NONE = 0,

	// Read accesses
	INDIRECT_BUFFER = 1 << 0,                                     // Read as an indirect buffer for drawing or dispatch
	INDEX_BUFFER = 1 << 1,                                        // Read as an index buffer for drawing
	VERTEX_BUFFER = 1 << 2,                                       // Read as a vertex buffer for drawing
	VERTEX_SHADER_READ_UNIFORM_BUFFER = 1 << 3,                   // Read as a uniform buffer in a vertex shader
	VERTEX_SHADER_READ_TEXTURE = 1 << 4,                          // Read as a sampled image/uniform texel buffer in a vertex shader
	VERTEX_SHADER_READ_OTHER = 1 << 5,                            // Read as any other resource in a vertex shader
	FRAGMENT_SHADER_READ_UNIFORM_BUFFER = 1 << 6,                 // Read as a uniform buffer in a fragment shader
	FRAGMENT_SHADER_READ_TEXTURE = 1 << 7,                        // Read as a sampled image/uniform texel buffer in a fragment shader
	FRAGMENT_SHADER_READ_COLOR_INPUT_ATTACHMENT = 1 << 8,         // Read as an input attachment with a color format in a fragment shader
	FRAGMENT_SHADER_READ_DEPTH_STENCIL_INPUT_ATTACHMENT = 1 << 9, // Read as an input attachment with a depth/stencil format in a fragment shader
	FRAGMENT_SHADER_READ_OTHER = 1 << 10,                         // Read as any other resource in a fragment shader
	COLOR_ATTACHMENT_READ = 1 << 11,                              // Read by standard blending/logic operations or subpass load operations
	DEPTH_STENCIL_ATTACHMENT_READ = 1 << 12,                      // Read by depth/stencil tests or subpass load operations
	COMPUTE_SHADER_READ_UNIFORM_BUFFER = 1 << 13,                 // Read as a uniform buffer in a compute shader
	COMPUTE_SHADER_READ_TEXTURE = 1 << 14,                        // Read as a sampled image/uniform texel buffer in a compute shader
	COMPUTE_SHADER_READ_OTHER = 1 << 15,                          // Read as any other resource in a compute shader
	TRANSFER_READ = 1 << 16,                                      // Read as the source of a transfer operation
	HOST_READ = 1 << 17,                                          // Read on the host
	PRESENT = 1 << 18,                                            // Read by the presentation engine

	// Write accesses
	VERTEX_SHADER_WRITE = 1 << 19,            // Written as any resource in a vertex shader
	FRAGMENT_SHADER_WRITE = 1 << 20,          // Written as any resource in a fragment shader
	COLOR_ATTACHMENT_WRITE = 1 << 21,         // Written as a color attachment during rendering, or via a subpass store op
	DEPTH_STENCIL_ATTACHMENT_WRITE = 1 << 22, // Written as a depth/stencil attachment during rendering, or via a subpass store op
	COMPUTE_SHADER_WRITE = 1 << 23,           // Written as any resource in a compute shader
	TRANSFER_WRITE = 1 << 24,                 // Written as the destination of a transfer operation
	HOST_PREINITIALIZED = 1 << 25,            // Data pre-filled by host before device access starts
	HOST_WRITE = 1 << 26,                     // Written on the host
};

enum class BarrierType {
	FULL,
	SPLIT_BEGIN,
	SPLIT_END,
};

struct FormatInfo
{
	const char* name;
	uint32 size;
	uint32 count;
	FormatType type;
	bool hasAlpha;
	bool hasDepth;
	bool hasStencil;
	bool isCompressed;
};

enum class AttributeName {
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
	COUNT,
};

enum class ClearFlagBit {
	NONE = 0,
	COLOR = 0x1,
	DEPTH = 0x2,
	STENCIL = 0x4,
	DEPTH_STENCIL = DEPTH | STENCIL,
	ALL = COLOR | DEPTH | STENCIL,
};

const FormatInfo& getFormatInfo(Format type);
const char* getAttributeName(AttributeName name);

END_OGS_GFX_NAMESPACE