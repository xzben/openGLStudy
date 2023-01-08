#include "CameraComponent.h"
#include "core/systems/RenderSystem.h"
#include "core/components/Transform.h"
#include "core/base/Node.h"
#include "core/components/Renderable.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(CameraComponent)

BEGIN_REFLEX_CLASS_FIELD(CameraComponent)
REFLEX_FIELD_NAME(Color, m_clearColor, "ClearColor")
END_REFLEX_CLASS_FIELD()


CameraComponent::CameraComponent()
{
	setRenderWindow(RenderSystem::getInstance()->getDefaultRenderWindow());
}

CameraComponent::~CameraComponent()
{
	setRenderWindow(nullptr);
}

void CameraComponent::initPerspective(float fieldOfView, float aspectRatio, float znear, float zfar)
{
	m_projection = CameraProjection::PERSPECTIVE;
	m_fieldOfView = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_nearPlane = znear;
	m_farPlane = zfar;
	m_matProj = Matrix4::perspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
	m_projectDirty = true;
	m_frusumDirty = true;
}

void CameraComponent::setFov(float fieldOfView)
{
	m_fieldOfView = fieldOfView;
	m_matProj = Matrix4::perspective(fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
	m_projectDirty = true;
	m_frusumDirty = true;
}

void CameraComponent::setAspect(float width, float height)
{
	m_aspectRatio = width/height;
	m_matProj = Matrix4::perspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
	m_projectDirty = true;
	m_frusumDirty = true;
}

void CameraComponent::initOrthographic(float zoomx, float zoomy, float znear, float zfar)
{
	m_projection = CameraProjection::ORTHO;

	m_zoom[0] = zoomx;
	m_zoom[1] = zoomy;

	m_nearPlane = znear;
	m_farPlane = zfar;

	m_matProj = Matrix4::orthograhic(m_zoom[0], m_zoom[1], m_nearPlane, m_farPlane);

	m_projectDirty = true;
	m_frusumDirty = true;
}

void CameraComponent::lookAt(Vector3 pos, Vector3 targetpos, Vector3 up)
{
	m_matView = Matrix4::lookAt(pos, targetpos, up);
	m_matViewInverse = m_matView.inverse();
	m_viewDirty = true;
	m_matViewInverse.decompose(&m_transform->m_pos, &m_transform->m_scale, &m_transform->m_rotation);
}

void CameraComponent::onLoad()
{
	m_transform = m_node->getComponent<Transform>();
	ASSERT(m_transform != nullptr, "must have tranform component");
}

void CameraComponent::onStart()
{
	RenderSystem::getInstance()->addCamera(this);
}

void CameraComponent::onStop()
{
	RenderSystem::getInstance()->removeCamera(this);
}

void CameraComponent::clear()
{
	
}

void CameraComponent::render(std::vector<Renderable*> renders)
{
	
}

void CameraComponent::handleViewportChange(const Rect& viewport)
{
	setAspect(viewport.width, viewport.height);
}

void CameraComponent::setRenderWindow(RenderWindow* window)
{

}

END_OGS_NAMESPACE