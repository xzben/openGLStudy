#include "Plane.h"
#include "render/RenderableComponent.h"
#include "PlaneMesh.h"
#include "render/Material.h"

BEGIN_NAMESPACE

class PlaneRender : public RenderableComponent
{
protected:
	Mesh* m_mesh;
	Material* m_material;
public:
	CREATE_FUNC(PlaneRender);

	PlaneRender();
	virtual ~PlaneRender();

	virtual void onLoad() override;
	virtual void render(RenderData* render) override;
	void initColor();
	void initSample();
};

Plane::Plane()
{

}

Plane::~Plane()
{

}

Plane* Plane::createColorMaterial()
{
	Plane* cube = Plane::create();
	PlaneRender* render = PlaneRender::create();
	render->initColor();
	cube->addComponent(render);

	return cube;
}

Plane* Plane::createSampleMaterial()
{
	Plane* cube = Plane::create();
	PlaneRender* render = PlaneRender::create();
	render->initSample();
	cube->addComponent(render);
	return cube;
}

void Plane::onLoad()
{

}

PlaneRender::PlaneRender()
{
	m_mesh = new PlaneMesh();
}

void PlaneRender::initColor()
{
	auto tex = ResourceManager::getInstance()->loadTexture("texture/metal.png");
	m_material = new Material(BuiltInShader::STANDARD_SHADER, tex);
	m_material->setDefine("MATERIAL_COLOR");
	m_material->setUniform("material.ambient", RGB(1.0f, 1.0f, 1.0f));
	m_material->setUniform("material.diffuse", RGB(1.0f, 1.0f, 1.0f));
	m_material->setUniform("material.specular", RGB(1.0f, 1.0f, 1.0f));
	m_material->setUniform("material.shininess", 32.f);
}
void PlaneRender::initSample()
{
	auto tex = ResourceManager::getInstance()->loadTexture("texture/metal.png");
	m_material = new Material(BuiltInShader::STANDARD_SHADER, tex);
	m_material->setDefine("MATERIAL_SAMPLE");

	m_material->setSubTexture("material.diffuse", tex);
	m_material->setSubTexture("material.specular", ResourceManager::getInstance()->loadTexture("texture/container2_specular.png"));
	m_material->setUniform("material.shininess", 32.f);
}

PlaneRender::~PlaneRender()
{
	DELETE_OBJ(m_mesh);
	DELETE_OBJ(m_material);
}

void PlaneRender::onLoad()
{

}

void PlaneRender::render(RenderData* render)
{
	this->doDraw(render, this->m_mesh, this->m_material);
}

END_NAMESPACE