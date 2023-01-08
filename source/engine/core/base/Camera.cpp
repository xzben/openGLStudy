#include "Camera.h"
#include "core/components/CameraComponent.h"
#include "core/components/Transform.h"
#include "core/systems/RenderSystem.h"
#include "core/view/Screen.h"


BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Camera)

BEGIN_REFLEX_CLASS_FIELD(Camera)
END_REFLEX_CLASS_FIELD()

Camera* Camera::createDefault3DCamera()
{
	auto cam = Camera::create();

	return cam;
}

Camera* Camera::createDefault2DCamera()
{
	auto cam = new Camera();

	return cam;
}

Camera::Camera()
{
	m_name = "MainCamera";
	m_transform = addComponent<Transform>();
	m_cameraCom = addComponent<CameraComponent>();
}

void Camera::setPerspective()
{
	Size size = Screen::getSize();

	m_cameraCom->initPerspective(45, size.width / size.height, 1, 1000);
}

void Camera::setOrtho()
{
	Size size = Screen::getSize();
	m_cameraCom->initOrthographic(size.width, size.height, 1, 1000);
}

Camera::~Camera()
{

}

END_OGS_NAMESPACE