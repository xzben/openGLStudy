#include "render_macro.h"

BEGIN_OGS_NAMESPACE

SampleInfo SampleInfo::DefaultTexture(TextureWrap::CLAMP_TO_EDGE, TextureFilter::NEAREST, TextureFilter::NEAREST);
SampleInfo SampleInfo::DefaultColorAttachment(TextureWrap::CLAMP_TO_EDGE, TextureFilter::LINEAR, TextureFilter::LINEAR);
SampleInfo SampleInfo::DefaultDepthStencilAttachment(TextureWrap::CLAMP_TO_EDGE, TextureFilter::LINEAR, TextureFilter::LINEAR);
END_OGS_NAMESPACE