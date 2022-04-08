#ifndef __2022_03_22_MAERIAL_H__
#define __2022_03_22_MAERIAL_H__

#include "base/Object.h"
#include <map>
#include "common.h"
#include "math/math.h"
#include "render/Color.h"
#include "resource/ResourceManager.h"

BEGIN_NAMESPACE


class Shader;
struct SHADER_DEFINE;
class RenderableComponent;
struct RenderData;
class Texture;
struct SubTexture;

struct Unifrom {
	uint8 size;
	std::string name;
	union
	{
		float values[4];
		float v1;
		fVec2 v2;
		fVec3 v3;
		fVec4 v4;
		Color color;
		RGB   rgb;
	};

	Unifrom() {
		memset(values, 0, 4*sizeof(float));
	}
};

class Material : public Object
{
protected:
	Texture* m_mainTexture;
	Shader* m_shader;

	//深度测试相关
	bool  m_depthTest; //是否启用深度测试
	bool  m_depthWriteable; //深度值是否写入
	DepthFunc m_depthFunc;  //深度检测函数

	//模板测试相关
	bool m_stencilTest; //是否启用模板测试
	uint8 m_stencilWriteMask; //所有写入模板缓存的数据都会与之 位与，如果设置 0x0相当于关闭写入
	uint8 m_stencilMask;  //配合  m_stecilRef m_stencilFunc 使用，这个mask只是用在比较过程中的，和写入无关
	uint8 m_stecilRef;  //模板测试 ref 值
	StencilFunc m_stencilFunc;  //模板测试函数
	StencilOp m_sfail;  // 模板测试失败 操作
	StencilOp m_dpfail; // 模板测试成功，深度测试失败的操作
	StencilOp m_dppass; // 模板测试成功，深度测试成功的操作

	//颜色混合相关操作
	bool m_blend; //颜色混合
	BlendFunc m_blendSrc;
	BlendFunc m_blendDst;

	//面剔除相关
	bool m_enableCullFace; // 是否启用面剔除
	FrontFace m_frontface;  //指定正面的顶点环绕顺序
	CullFace  m_cullface; //指定剔除面

	std::vector<SubTexture*> m_subTextures;
	std::map<std::string, SubTexture*> m_mapSubTextures;
	std::vector<Unifrom*> m_uniforms;
	std::map<std::string, Unifrom*> m_mapUnifroms;

	std::vector<SHADER_DEFINE*> m_defines;
	std::map<std::string, SHADER_DEFINE*> m_mapDefines;
	bool m_defineChange;

	Unifrom* getUniform(const std::string& name, bool create = false);
	void pushUniform(Unifrom* uniform);
	void addDefine(SHADER_DEFINE* define);

	
public:
	Material(Shader* shader);
	Material(BuiltInShader shaderId);
	Material(Shader* shader, Texture* mainTexture);
	Material(BuiltInShader shaderId, Texture* mainTexture);
	Material(Shader* shader, const std::string& texturepath);
	Material(BuiltInShader shaderId, const std::string& texturepath);

	virtual ~Material();


	void init(Shader* shader, Texture* mainTexture);
	void setEnableDepthTest(bool enable); //是否启用深度测试
	void setEnableDepthWrite(bool enable); //是否启用深度写入
	void setDepthFunc(DepthFunc func); //设置深度函数

	void setSubTexture(const std::string& name, Texture* tex);
		
	void setUniform(const std::string& name, const float value);
	void setUniform(const std::string& name, const fVec2& value);
	void setUniform(const std::string& name, const fVec3& value);
	void setUniform(const std::string& name, const fVec4& value);
	void setUniform(const std::string& name, const Color& value);
	void setUniform(const std::string& name, const RGB& value);
	

	SHADER_DEFINE* getDefine(const std::string& name, bool create = false);
	void setDefine(const std::string& name);
	void setDefine(const std::string& name, const std::string& value);
	void setDefine(const std::string& name, float value);
	void setDefine(const std::string& name, int value);
	void deleteDefine(const std::string& name);

	virtual bool beforeDraw(RenderData* render, RenderableComponent* com);
	virtual bool afterDraw();


};

END_NAMESPACE

#endif//__2022_03_22_MAERIAL_H__