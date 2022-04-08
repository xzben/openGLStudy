#include "Shader.h"
#include "utils/FileUtils.h"
#include <glad/glad.h>
#include "base//Node.h"
#include "base/Application.h"
#include "base/Camera.h"
#include "light/Light.h"
#include "utils/Utils.h"
#include "light/LightManager.h"
#include <regex>

BEGIN_NAMESPACE

const char* SHADER_VERSION_HEAD = "#version 330 core\r\n";

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
	m_vSource = getShaderContent(vertextPath);
	m_fSource = getShaderContent(fragmentPath);
	this->m_id = glCreateProgram();
	m_compiled = false;
}

const char** Shader::getFullShaderSource(const std::string& content, const std::vector<SHADER_DEFINE*>* defines, int& size)
{
	size = 2;
	if(defines != nullptr)
		size += defines->size();

	const char** ret = new const char*[size];
	
	ret[0] = SHADER_VERSION_HEAD;
	for (int i = 0; i < size - 2; i++)
	{
		ret[i+1] = defines->at(i)->value.c_str();
	}
	ret[size - 1] = content.c_str();
	return ret;
}

bool Shader::recompile(const std::vector<SHADER_DEFINE*>* defines)
{
	int  success;
	char infoLog[GL_ERROR_MSG_SIZE];

	int size;
	const char** vsource = getFullShaderSource(m_vSource, defines, size);
	
	uint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, size, vsource, NULL);
	glCompileShader(vertexShader);
	delete[] vsource;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	const char** fsource = getFullShaderSource(m_fSource, defines, size);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, size, fsource, NULL);
	glCompileShader(fragmentShader);
	delete[] fsource;

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	glAttachShader(this->m_id, vertexShader);
	glAttachShader(this->m_id, fragmentShader);
	glLinkProgram(this->m_id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(this->m_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->m_id, GL_ERROR_MSG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK PROGRAM ERROR\n" << infoLog << std::endl;
		return false;
	}

	m_compiled = true;

	return true;
}

Shader::~Shader() 
{
	if (this->m_id > 0) {
		glDeleteProgram(this->m_id);
	}
}

void Shader::use() 
{
	if (!m_compiled)
		this->recompile(nullptr);

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

void Shader::setColorRGB(const std::string& name, const Color& value) const
{
	glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), value.r, value.g, value.b);
}

void Shader::setRGB(const std::string& name, const RGB& value)const
{
	glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), value.r, value.g, value.b);
}

void Shader::setFloatValues(const std::string& name, float value[], int size)
{
	CC_ASSERT(size > 0 && size <= 4);
	auto location = (glGetUniformLocation(this->m_id, name.c_str()));
	switch (size)
	{
	case 1:
	{
		glUniform1f(location, value[0]);
		break;
	}
	case 2:
	{
		glUniform2f(location, value[0], value[1]);
		break;
	}
	case 3:
	{
		glUniform3f(location, value[0], value[1], value[2]);
		break;
	}
	case 4:
	{
		glUniform4f(location, value[0], value[1], value[2], value[3]);
		break;
	}
	}
}

void Shader::setMat3(const std::string& name, const fMat3& value)const {

	glUniformMatrix3fv(
		glGetUniformLocation(this->m_id, name.c_str()), //uniform ��ַ
		1,   //��������
		GL_FALSE,  // �Ƿ���Ҫת�þ���  ������ �о��� ��ת�����������Ǳ���ʹ�õ���������������Բ���Ҫת��
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

	LightManager::getInstance();

	if (light != nullptr)
	{
		const LightShaderData& lightInfo = light->getLightShaderData();

		setVec3(SHADER_LIGHT_POS, lightInfo.pos);
		setRGB(SHADER_LIGHT_AMBIENT_COLOR, lightInfo.ambient);
		setRGB(SHADER_LIGHT_DIFFUSE_COLOR, lightInfo.diffuse);
		setRGB(SHADER_LIGHT_SPECULAR_COLOR, lightInfo.specular);
		setVec3(SHADER_LIGHT_STRENGTH, lightInfo.strength);
	}
	
	setColor(SHADER_UNIFORM_COLOR, node->getDrawColor());
	setVec3(SHADER_CAMERA_POS, cam->getWorldPosition());
}

Shader* Shader::clone()
{
	Shader* obj = new Shader();
	obj->m_vSource = m_vSource;
	obj->m_fSource = m_fSource;
	obj->m_compiled = false;
	obj->m_id = glCreateProgram();

	return obj;
}

END_NAMESPACE