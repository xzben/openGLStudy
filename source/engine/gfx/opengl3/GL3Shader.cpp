#include "GL3Shader.h"
#include "glad/glad.h"
#include "utils/Utils.h"

BEGIN_OGS_GFX_NAMESPACE

const uint32 INVALID_BINDING = ~0u;
IMPLEMENT_RUNTIME_CLASS(GL3Shader)

GL3Shader::GL3Shader()
{
	m_handle = 0;
}

GL3Shader::~GL3Shader()
{
	if(m_handle > 0)
		glDeleteProgram(m_handle);
}

bool GL3Shader::initilize(ShaderInfo* info)
{
	Super::initilize(info);
	std::vector<GLint> shaders;
	GLint status;

	for (auto it = m_info->stages.begin(); it != m_info->stages.end(); it++)
	{
		AutoRef<ShaderStage> stage = *it;

		GLenum glshaderStage = 0;
		std::string shaderStageStr;

		switch (stage->stage)
		{
		case ShaderStageFlagBit::VERTEX:
		{
			shaderStageStr = "Vertex Shader";
			glshaderStage = GL_VERTEX_SHADER;
			break;
		}
		case ShaderStageFlagBit::FRAGMENT:
		{
			shaderStageStr = "Fragment Shader";
			glshaderStage = GL_FRAGMENT_SHADER;
			break;
		}
		case ShaderStageFlagBit::COMPUTE:
		{
			shaderStageStr = "Compute Shader";
			glshaderStage = GL_COMPUTE_SHADER;
			break;
		}
		default:
		{
			CC_ASSERT(false);
			return false;
		}
		}

		uint32 version = 300;
		std::string source = OGS::Utils::string_format("##version %u es\n", version) + stage->source;
		GLint shader = glCreateShader(glshaderStage);
		
		const char* ptr_source = source.c_str();
		GL_CHECK(glShaderSource(shader, 1, (char**)&ptr_source, nullptr));
		GL_CHECK(glCompileShader(shader));
		GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
		if (status != GL_TRUE) {
			GLint logSize = 0;
			GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize));

			++logSize;
			auto* logs = static_cast<GLchar*>(malloc(logSize));
			GL_CHECK(glGetShaderInfoLog(shader, logSize, nullptr, logs));

			CCLOG_ERROR("%s in %s compilation failed.", shaderStageStr.c_str(), info->name.c_str());
			CCLOG_ERROR(logs);
			free(logs);
			GL_CHECK(glDeleteShader(shader));
			shader = 0;
			return false;
		}
		shaders.push_back(shader);
	}
	GLuint program;
	GL_CHECK(program = glCreateProgram());
	m_handle = program;
	for (auto it = shaders.begin(); it != shaders.end(); it++)
	{
		GL_CHECK(glAttachShader(program, *it));
	}

	GL_CHECK(glLinkProgram(program));

	for (auto it = shaders.begin(); it != shaders.end(); it++)
	{
		GL_CHECK(glDetachShader(program, *it));
		GL_CHECK(glDeleteShader(*it));
	}

	GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &status));
	if (status != 1) {
		CCLOG_ERROR("Failed to link Shader [%s].", info->name.c_str());
		GLint logSize = 0;
		GL_CHECK(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize));
		if (logSize) {
			++logSize;
			auto* logs = static_cast<GLchar*>(malloc(logSize));
			GL_CHECK(glGetProgramInfoLog(program, logSize, nullptr, logs));

			CCLOG_ERROR(logs);
			free(logs);
			return false;
		}
	}

	CCLOG_INFO("Shader '%s' compilation succeeded.", info->name.c_str());

	GLint attrMaxLength = 0;
	GLint attrCount = 0;
	GL_CHECK(glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attrMaxLength));
	GL_CHECK(glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attrCount));

	GLchar glName[256];
	GLsizei glLength;
	GLsizei glSize;
	GLenum glType;

	info->attributes.resize(attrCount);
	for (GLint i = 0; i < attrCount; ++i) {
		AutoRef<Attribute> attr = new Attribute();
		info->attributes.push_back(attr);
		memset(glName, 0, sizeof(glName));
		GL_CHECK(glGetActiveAttrib(program, i, attrMaxLength, &glLength, &glSize, &glType, glName));
		char* offset = strchr(glName, '[');
		if (offset) {
			glName[offset - glName] = '\0';
		}

		GL_CHECK(attr->location = glGetAttribLocation(program, glName));
		attr->name = glName;
		//attr.type = mapType(glType);
		//attr.count = glSize;
		//attr.size = gpuInput.stride * gpuInput.count;
		//attr.glType = glType;
	}


	// create buffers
	GLint blockCount;
	GL_CHECK(glGetProgramiv(program, GL_ACTIVE_UNIFORM_BLOCKS, &blockCount));
	GLint bufferCount = 0;
	//if (device->constantRegistry()->glMinorVersion > 0) {
		GL_CHECK(glGetProgramInterfaceiv(program, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &bufferCount));
	//}
	 for (GLint i = 0; i < blockCount; ++i) {
		AutoRef<UniformBlock> block = new UniformBlock;
		info->blocks.push_back(block);
        memset(glName, 0, sizeof(glName));
        GL_CHECK(glGetActiveUniformBlockName(program, i, 255, &glLength, glName));

        char *offset = strchr(glName, '[');
        if (offset) {
            glName[offset - glName] = '\0';
        }
		block->name = glName;	
		block->binding = INVALID_BINDING;
		block->set = INVALID_BINDING;

        //for (size_t b = 0; b < gpuShader->blocks.size(); ++b) {
        //    UniformBlock &block = gpuShader->blocks[b];
        //    if (block.name == glBlock.name) {
        //        glBlock.set = block.set;
        //        glBlock.binding = block.binding;
        //        glBlock.glBinding = block.binding + device->bindingMappings().blockOffsets[block.set];
        //        GL_CHECK(glUniformBlockBinding(gpuShader->glProgram, i, glBlock.glBinding));
        //        break;
        //    }
        //}
    }


	return true;
}

END_OGS_GFX_NAMESPACE