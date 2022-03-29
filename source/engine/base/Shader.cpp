#include "Shader.h"
#include "utils/FileUtils.h"
#include <glad/glad.h>
#include "base//Node.h"
#include "base/Application.h"
#include "base/Camera.h"
#include "light/Light.h"
#include <regex>

BEGIN_NAMESPACE

std::string getShaderContent(const std::string& path)
{
	std::string source = FileUtils::getInstance()->getString(path);
	if (source == "") return source;

	std::regex import_reg("#import\\s*<\\s*([\\w./]*)\\s*>");
	std::smatch result;

	std::string::const_iterator itstart = source.begin();
	std::string::const_iterator itend = source.end();

	std::string temp;
	std::string imppath;

	while (std::regex_search(itstart, itend, result, import_reg))
	{
		std::string path = result[1];
		std::string subsouce = FileUtils::getInstance()->getString(path);
		if (subsouce != "")
		{
			source.replace(result[0].first, result[0].second, subsouce);
		}
		else
		{
			CCLOGERROR("shader source failed to import %s", path.c_str());
			CC_ASSERT(false);
		}	

		itstart = source.begin();
		itend = source.end();
	}

	return source;
}

Shader::Shader(const std::string& vertextPath, const std::string& fragmentPath) 
	: m_id(-1)
{
	this->init(vertextPath, fragmentPath);
}

Shader::Shader(const std::string& filepath)
	: m_id(-1)
{
	this->init(filepath + ".vs", filepath + ".fs");
}

void Shader::init(const std::string& vertextPath, const std::string& fragmentPath) 
{
	std::string vsource = getShaderContent(vertextPath);
	std::string fsource = getShaderContent(fragmentPath);

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


void Shader::setVec3(const std::string& name, const fVec3& value) const {
	glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, const fVec4& value) const {
	glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setColor(const std::string& name, const Color& value) const
{
	glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), value.r, value.g, value.b, value.a);
}

void Shader::setMat3(const std::string& name, const fMat3& value)const {

	glUniformMatrix3fv(
		glGetUniformLocation(this->m_id, name.c_str()), //uniform 地址
		1,   //矩阵数量
		GL_FALSE,  // 是否需要转置矩阵  行主序 列矩阵 的转换，由于我们本身使用的是列主序矩阵所以不需要转置
		value.m_data);
}

void Shader::setMat4(const std::string& name, const fMat4& value)const {
	glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 
		1, 
		GL_FALSE, 
		value.m_data);
}

void Shader::initCommonUniform(RenderData* render, Node* node)
{
	setVec3(SHADER_COMMON_UNIFORM_TIMER, Application::getInstance()->getShaderTimer());

	Camera* cam = render->mainCamera;
	Light* light = render->mainLight;

	const fMat4& model = node->getShaderModel();
	const fMat4 view = cam->getViewMatrix();
	const fMat4 projection = cam->getProjectMatrix();
	const fMat4 mvp = cam->getViewProjectMatrix()*model;

	setMat4(SHADER_COMMON_UNIFORM_MODEL, model);
	setMat4(SHADER_COMMON_UNIFORM_VIEW, view);
	setMat4(SHADER_COMMON_UNIFORM_PROJECTION, projection);
	setMat4(SHADER_COMMON_UNIFORM_MVP, mvp);

	if (light != nullptr)
	{
		setVec3(SHADER_LIGHT_POS, light->getWorldPosition());
		setColor(SHADER_LIGHT_COLOR, light->getLightColor());
		setFloat(SHADER_LIGHT_AMBIENT_STRENGTH, light->getAmbientStrength());
	}
	
	setColor(SHADER_UNIFORM_COLOR, node->getDrawColor());
}

END_NAMESPACE