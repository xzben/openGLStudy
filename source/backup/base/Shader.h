#ifndef __SHADER_2021_09_06_H__
#define __SHADER_2021_09_06_H__

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "common.h"
#include "math/math.h"
#include "base/Object.h"
#include "render/Color.h"
#include "render/RenderData.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE


class Node;

struct SHADER_DEFINE
{
	std::string name;
	std::string value;
};

class Shader : public Object, public NonCopyable
{
public:
	GL_HANDLE m_id;
	std::string m_vSource;
	std::string m_fSource;
	bool m_compiled;
	void initCommonUniform(RenderData* cam, Node* node);
protected:
	void init(const std::string& vertextPath, const std::string& fragmentPath);
	
	const char** getFullShaderSource(const std::string& content, const std::vector<SHADER_DEFINE*>* defines, int& size);
	Shader() {}
public:

	Shader(const std::string& vertextPath, const std::string& fragmentPath);
	Shader(const std::string& filepath);

	virtual ~Shader();
	Shader* clone();
	
	void use();
	void unuse();
	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string &name, int value)const;
	void setFloat(const std::string &name, float value)const;
	void setVec3(const std::string& name, const iVec3& value) const;
	void setVec3(const std::string& name, const fVec3& value) const;
	void setVec4(const std::string& name, const fVec4& value) const;
	void setMat3(const std::string& name, const fMat3& value)const;
	void setMat4(const std::string& name, const fMat4& value)const;
	void setColor(const std::string& name, const Color& value) const;
	void setColorRGB(const std::string& name, const Color& value) const;
	void setRGB(const std::string& name, const RGB& value)const;
	void setFloatValues(const std::string& name, float value[], int size);
	bool recompile(const std::vector<SHADER_DEFINE*>* defines);

};

END_NAMESPACE

#endif // !__SHADER_2021_09_06_H__
