#include "GL3Sampler.h"
#include "glad/glad.h"

BEGIN_OGS_GFX_NAMESPACE

const GLenum GLES3_WRAPS[] = {
	GL_REPEAT,
	GL_MIRRORED_REPEAT,
	GL_CLAMP_TO_EDGE,
	GL_CLAMP_TO_EDGE,
};

static void getFilter(GLuint& minFilter, GLuint& magFilter, SamplerInfo* info)
{
	if (info->minFilter == Filter::LINEAR || info->minFilter == Filter::ANISOTROPIC) 
	{
		if (info->mipFilter == Filter::LINEAR || info->mipFilter == Filter::ANISOTROPIC)
		{
			minFilter = GL_LINEAR_MIPMAP_LINEAR;
		}
		else if (info->mipFilter == Filter::POINT)
		{
			minFilter = GL_LINEAR_MIPMAP_NEAREST;
		}
		else
		{
			minFilter = GL_LINEAR;
		}
	}
	else
	{
		if (info->mipFilter == Filter::LINEAR || info->mipFilter == Filter::ANISOTROPIC)
		{
			minFilter = GL_NEAREST_MIPMAP_LINEAR;
		}
		else if (info->mipFilter == Filter::POINT)
		{
			minFilter = GL_LINEAR_MIPMAP_NEAREST;
		}
		else
		{
			minFilter = GL_NEAREST;
		}
	}

	if (info->magFilter == Filter::LINEAR || info->magFilter == Filter::ANISOTROPIC)
	{
		magFilter = GL_LINEAR;
	}
	else
	{
		magFilter = GL_NEAREST;
	}
}

GL3Sampler::GL3Sampler(SamplerInfo* info, HASH_CODE hash)
	:Sampler(info, hash)
{
	
}

GLuint GL3Sampler::getGLSampler(uint16 minlod, uint16 maxLod)
{
	HASH_CODE hash = (minlod << 16) + maxLod;

	if (m_cache.find(hash) == m_cache.end())
	{
		SamplerInfo* info = m_info.get();
		GLuint glhandle;
		GL_CHECK(glGenSamplers(1, &glhandle));

		GLuint glMinFilter = 0;
		GLuint glMagFilter = 0;
		getFilter(glMinFilter, glMagFilter, info);

		GLuint glWrapS = GLES3_WRAPS[(int)info->addressU];
		GLuint glWrapT = GLES3_WRAPS[(int)info->addressV];;
		GLuint glWrapR = GLES3_WRAPS[(int)info->addressW];;

		GL_CHECK(glSamplerParameteri(glhandle, GL_TEXTURE_MIN_FILTER, glMinFilter));
		GL_CHECK(glSamplerParameteri(glhandle, GL_TEXTURE_MAG_FILTER, glMagFilter));
		GL_CHECK(glSamplerParameteri(glhandle, GL_TEXTURE_WRAP_S, glWrapS));
		GL_CHECK(glSamplerParameteri(glhandle, GL_TEXTURE_WRAP_T, glWrapT));
		GL_CHECK(glSamplerParameteri(glhandle, GL_TEXTURE_WRAP_R, glWrapR));		
		GL_CHECK(glSamplerParameterf(glhandle, GL_TEXTURE_MIN_LOD, (GLfloat)minlod));
		GL_CHECK(glSamplerParameterf(glhandle, GL_TEXTURE_MAX_LOD, (GLfloat)maxLod));

		m_cache[hash] = glhandle;
	}

	return m_cache[hash];
	
}
GL3Sampler::~GL3Sampler()
{
	std::vector<GLuint> glsamplers;
	for (auto it = m_cache.begin(); it != m_cache.end(); it++)
	{
		glsamplers.push_back(it->second);
	}
	GL_CHECK(glDeleteSamplers(glsamplers.size(), glsamplers.data()));
}

END_OGS_GFX_NAMESPACE