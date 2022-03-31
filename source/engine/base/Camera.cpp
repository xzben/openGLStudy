#include "Camera.h"
#include "math/MathUtil.h"
#include "window/Window.h"


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

	if (camera3d)
	{
		initPerspective(60.0f, size.width / size.height, 0.1f, 100.0f);
		this->setRotation(-60.0f, 0.0f, 0.0f);
		this->setPosition(0.0f, 6.0f, 3.0f);
	}
	else
	{
		initOrthographic(10, 10, -7.5f, 7.5f);
		setPosition(0, 0, 3.0);
		setRotation(0, 0, 0);
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

	m_matProjection = MathUtil::createOrthographic(m_zoom[0], m_zoom[1], m_nearPlane, m_farPlane);
	
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
	getViewMatrix();

	if (m_projectDirty)
	{
		m_matViewProjection = m_matProjection * m_matView;
		m_projectDirty = false;
	}

	return m_matViewProjection;
}

const fMat4& Camera::getViewMatrix()
{
	if (m_type == Camera::Type::PERSPECTIVE)
	{
		if (m_viewDirty) {
			m_matView = this->m_matModel.inverse();
			m_matViewProjection = m_matProjection * m_matView;
			m_viewDirty = false;
			m_projectDirty = false;
		}
	}

	return m_matView;
}

const fMat4& Camera::getProjectMatrix()
{
	return m_matProjection;
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