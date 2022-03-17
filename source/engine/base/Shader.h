#ifndef __SHADER_2021_09_06_H__
#define __SHADER_2021_09_06_H__

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "common.h"
#include "math/math.h"

class Node;

class Shader 
{
public:
	void initCommonUniform(Node* node);
protected:
	void init(const std::string& vertextPath, const std::string& fragmentPath);
public:
	uint m_id;
	Shader(const std::string& vertextPath, const std::string& fragmentPath);
	virtual ~Shader();
	void use();
	void unuse();
	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string &name, int value)const;
	void setFloat(const std::string &name, float value)const;
	void setVec3(const std::string& name, const fVec3& value) const;
	void setVec4(const std::string& name, const fVec4& value) const;
	void setMat3(const std::string& name, const fMat3& value)const;
	void setMat4(const std::string& name, const fMat4& value)const;
	

};

#endif // !__SHADER_2021_09_06_H__
