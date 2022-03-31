#include "Cube.h"
#include "render/RenderableComponent.h"
#include "CubeMesh.h"
#include "render/Material.h"

BEGIN_NAMESPACE

class CubeRender : public RenderableComponent
{
protected:
	Mesh* m_mesh;
	Material* m_material;
public:
	CREATE_FUNC(CubeRender);

	CubeRender();
	virtual ~CubeRender();

	virtual void onLoad() override;
	virtual void render(RenderData* render) override;
};

Cube::Cube()
{

}

Cube::~Cube()
{

}

void Cube::onLoad()
{
	this->addComponent(CubeRender::create());
}

CubeRender::CubeRender()
{
	m_mesh = new CubeMesh();
	m_material = new Material(BuiltInShader::STANDARD_SHADER);
	m_material->setUniform("material.ambient", RGB(1.0f, 0.5f, 0.31f));
	m_material->setUniform("material.diffuse", RGB(1.0f, 0.5f, 0.31f));
	m_material->setUniform("material.specular", RGB(0.5f, 0.5f, 0.5f));
	m_material->setUniform("material.shininess", 32.f);
}

CubeRender::~CubeRender()
{
	DELETE_OBJ(m_mesh);
	DELETE_OBJ(m_material);
}

void CubeRender::onLoad()
{

}

void CubeRender::render(RenderData* render)
{
	this->doDraw(render, this->m_mesh, this->m_material);
}

END_NAMESPACE