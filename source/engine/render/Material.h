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

	//��Ȳ������
	bool  m_depthTest; //�Ƿ�������Ȳ���
	bool  m_depthWriteable; //���ֵ�Ƿ�д��
	DepthFunc m_depthFunc;  //��ȼ�⺯��

	//ģ��������
	bool m_stencilTest; //�Ƿ�����ģ�����
	uint8 m_stencilWriteMask; //����д��ģ�建������ݶ�����֮ λ�룬������� 0x0�൱�ڹر�д��
	uint8 m_stencilMask;  //���  m_stecilRef m_stencilFunc ʹ�ã����maskֻ�����ڱȽϹ����еģ���д���޹�
	uint8 m_stecilRef;  //ģ����� ref ֵ
	StencilFunc m_stencilFunc;  //ģ����Ժ���
	StencilOp m_sfail;  // ģ�����ʧ�� ����
	StencilOp m_dpfail; // ģ����Գɹ�����Ȳ���ʧ�ܵĲ���
	StencilOp m_dppass; // ģ����Գɹ�����Ȳ��Գɹ��Ĳ���

	//��ɫ�����ز���
	bool m_blend; //��ɫ���
	BlendFunc m_blendSrc;
	BlendFunc m_blendDst;

	//���޳����
	bool m_enableCullFace; // �Ƿ��������޳�
	FrontFace m_frontface;  //ָ������Ķ��㻷��˳��
	CullFace  m_cullface; //ָ���޳���

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
	void setEnableDepthTest(bool enable); //�Ƿ�������Ȳ���
	void setEnableDepthWrite(bool enable); //�Ƿ��������д��
	void setDepthFunc(DepthFunc func); //������Ⱥ���

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