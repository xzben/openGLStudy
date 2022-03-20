#include "Camera.h"

Camera* Camera::createFrustum()
{
	Camera* obj = new Camera();
	if (obj)
		obj->onLoad();

	return obj;
}

Camera* Camera::createPerspective()
{
	Camera* obj = new Camera();
	if (obj)
		obj->onLoad();

	return obj;
}

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::isCameraVisible(uint mask)
{
	return m_visibility & mask != 0;
}

void Camera::setMask(uint mask)
{
	m_visibility = mask;
}

void Camera::addGroup(uint mask)
{
	m_visibility |= mask;
}