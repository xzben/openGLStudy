#include "Camera.h"
#include "window/Window.h"
#include "math/Vec3.h"

BEGIN_NAMESPACE

Camera* Camera::createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
	Camera* obj = new Camera();
	if (obj)
	{
		obj->initOrthographic(zoomX, zoomY, nearPlane, farPlane);
		obj->onLoad();
	}


	return obj;
}

Camera* Camera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	Camera* obj = new Camera();
	if (obj)
	{
		obj->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
		obj->onLoad();
	}
	
	return obj;
}

Camera* Camera::createDefault(bool camera3d)
{
	Camera* obj = new Camera();
	if (obj)
	{
		obj->initDefault(camera3d);
		obj->onLoad();
	}

	return obj;
}

Camera::Camera()
	:m_up(0, 1, 0)
{

}

Camera::~Camera()
{

}

bool Camera::initDefault(bool camera3d)
{
	const Size& size = Window::getInstance()->getWinSize();

	if (camera3d) {
		float zeye = size.height / 1.1566f;
		initPerspective(60, size.width / size.height, 10, zeye + size.height / 2.0);
		POSITION eye(size.width / 2, size.height / 2.0, zeye);
		POSITION(size.width / 2, size.height / 2, 0.0f);
		fVec3 up(0.0f, 1.0f, 0.0);

		//this->setPosition(eye);
	}

	return true;
}

bool Camera::initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	m_type = Camera::Type::PERSPECTIVE;
	m_fieldOfView = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_matProjection = MathUtil::createPerspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
	m_projectDirty = true;
	m_frusumDirty = true;

	return true;
}

bool Camera::initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
	m_type = Camera::Type::ORTHOGRAPHIC;

	m_zoom[0] = zoomX;
	m_zoom[1] = zoomY;

	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_matProjection = MathUtil::createOrthographicOffCenter(0, m_zoom[0], 0, m_zoom[1], m_nearPlane, m_farPlane);

	m_projectDirty = true;
	m_frusumDirty = true;

	return true;
}

bool Camera::isCameraVisible(uint mask)
{
	return (m_visibility & mask) != 0;
}

void Camera::setMask(uint mask)
{
	m_visibility = mask;
}

void Camera::addGroup(uint mask)
{
	m_visibility |= mask;
}

const fMat4& Camera::getViewProjectMatrix()
{
	if (m_viewDirty) {
		m_matView = MathUtil::cameraLookAt(m_pos, m_rotation, m_up);
	}

	if (m_viewDirty || m_projectDirty)
	{
		m_matViewProjection = m_matProjection * m_matView;
		m_viewDirty = false;
		m_projectDirty = false;
	}

	return m_matViewProjection;
}

void Camera::setPosition(float x, float y, float z)
{
	Node::setPosition(x, y, z);
	m_viewDirty = true;
}

void Camera::setRotation(float x, float y, float z)
{
	Node::setRotation(x, y, z);
	m_viewDirty = true;
}

END_NAMESPACE