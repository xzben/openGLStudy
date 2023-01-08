#include "light/Light.h"
#include "render/RenderableComponent.h"
#include "render/base/Mesh.h"
#include "resource/ResourceManager.h"
#include "LightManager.h"
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
	: m_lightColor(1.0f, 1.0f, 1.0f)
{

}

Light::~Light()
{

}

void Light::doStart()
{
	Node::doStart();
	LightManager::getInstance()->addLight(this);
}

void Light::doStop()
{
	Node::doStop();
	LightManager::getInstance()->removeLight(this);
}

void Light::setLightColor(const Color &color)
{
	m_lightColor = color;
}

const Color& Light::getLightColor() const
{
	return m_lightColor;
}


void Light::doLoad()
{
	this->addComponent(LightRender::create());
	Node::doLoad();
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
	DELETE_OBJ(this->m_mesh);
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

