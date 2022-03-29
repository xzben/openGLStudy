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
	: m_ambientStrength(0.1f)
	, m_specularStrength(0.5f)
{

}

Light::~Light()
{

}

void Light::setLightColor(const Color& color)
{
	m_lightColor = color;
}
const Color& Light::getLightColor()
{
	return m_lightColor;
}

POSITION Light::getLightPos()
{
	return this->getWorldPosition();
}


void Light::onLoad()
{
	this->addComponent(LightRender::create());
}

LightRender::LightRender()
	: m_mesh(nullptr)
{
	this->m_mesh = new Mesh();
	this->m_shader = ResourceManager::getInstance()->loadShader("light_mesh");
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

