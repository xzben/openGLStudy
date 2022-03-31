#include "light/Light.h"
#include "render/RenderableComponent.h"
#include "render/base/Mesh.h"
#include "resource/ResourceManager.h"
#include "base/Shader.h"

BEGIN_NAMESPACE


class LightRender : public RenderableComponent
{
protected:
	Shader* m_shader;
	Mesh* m_mesh;
public:
	CREATE_FUNC(LightRender);
	LightRender();
	virtual ~LightRender();
	virtual void render(RenderData* render) override;
	bool init();
	virtual void onLoad() override;
};

Light::Light()
	: m_unitColor(true)
	, m_lightColor(1.0f, 1.0f, 1.0f)
{
	m_lightInfo.diffuse = m_lightInfo.specular = m_lightInfo.ambient = RGB(1.0f, 1.0f, 1.0f);
	m_lightInfo.strength = fVec3(1.0f, 1.0f, 1.0f);
}

Light::~Light()
{

}

const LightShaderData& Light::getLightShaderData()
{
	m_lightInfo.pos = this->getWorldPosition();

	return m_lightInfo;
}

void Light::setLightColor(const Color &color)
{
	m_lightColor = color;
	if (m_unitColor)
	{
		RGB rgb = color.toRGB();
		m_lightInfo.ambient = rgb;
		m_lightInfo.diffuse = rgb;
		m_lightInfo.specular = rgb;
	}
}

void Light::setAmbientColor(const RGB& color)
{
	m_unitColor = false;
	m_lightInfo.ambient = color;
}

const RGB& Light::getAmbientColor()const
{
	return m_lightInfo.ambient;
}

void Light::setDiffuseColor(const RGB& color)
{
	m_unitColor = false;
	m_lightInfo.diffuse = color;
}

const RGB& Light::getDiffuseColor() const
{
	return m_lightInfo.diffuse;
}

void Light::setSpecularColor(const RGB& color)
{
	m_unitColor = false;
	m_lightInfo.specular = color;
}

const RGB& Light::getSpecularColor() const
{
	return m_lightInfo.specular;
}

const Color& Light::getLightColor() const
{
	return m_lightColor;
}


void Light::onLoad()
{
	this->addComponent(LightRender::create());
}

LightRender::LightRender()
	: m_mesh(nullptr)
{
	this->m_mesh = new Mesh();
	this->m_shader = ResourceManager::getInstance()->loadShader("shader/light_mesh");
}

LightRender::~LightRender()
{
	SAFE_DEL_REF(this->m_shader);
	SAFE_DEL_REF(this->m_mesh);
}

void LightRender::onLoad()
{
	RenderableComponent::onLoad();
	this->init();
}
bool LightRender::init()
{
	float vertices[] = {
		//----- pos ------- |
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		
		-0.1f, -0.1f,  0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,

		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,

		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,

		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,

		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
	};

	this->m_mesh->setup(vertices, 36, nullptr, 0, VerticleMember::POS);

	return true;
}

void LightRender::render(RenderData* render)
{
	this->doDraw(render, this->m_mesh, this->m_shader, nullptr);
}

END_NAMESPACE

