#include "Shader.h"
#include "utils/FileUtils.h"
#include <glad/glad.h>

Shader::Shader(const std::string& vertextPath, const std::string& fragmentPath) 
	: m_id(-1)
{
	this->init(vertextPath, fragmentPath);
}

void Shader::init(const std::string& vertextPath, const std::string& fragmentPath) 
{
	std::string vsource = FileUtils::getInstance()->getString(vertextPath);
	std::string fsource = FileUtils::getInstance()->getString(fragmentPath);

	int  success;
	char infoLog[GL_ERROR_MSG_SIZE];

	uint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* source = (const char*)vsource.c_str();
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = (const char*)fsource.c_str();
	glShaderSource(fragmentShader, 1, &source, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return;
	}

	this->m_id = glCreateProgram();
	glAttachShader(this->m_id, vertexShader);
	glAttachShader(this->m_id, fragmentShader);
	glLinkProgram(this->m_id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(this->m_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->m_id, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK PROGRAM ERROR\n" << infoLog << std::endl;
		return;
	}


}

Shader::~Shader() 
{
	if (this->m_id > 0) {
		glDeleteProgram(this->m_id);
	}
}

void Shader::use() 
{
	glUseProgram(this->m_id);
}


void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::setBool(const std::string &name, bool value)const {
	glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value)const {
	glUniform1f(glGetUniformLocation(this->m_id, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value)const {
	glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), value);
}


void Shader::setVec3(const std::string& name, fVec3 value) const {
	glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, fVec4 value) const {
	glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), value.x, value.y, value.z, value.w);
}