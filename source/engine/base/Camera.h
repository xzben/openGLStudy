#ifndef __2022_03_18_CAMERA_H__
#define __2022_03_18_CAMERA_H__

#include "base/Node.h"
#include "common.h"
#include "math/Mat4.h"

class Camera : public Node
{
public:
	enum class Type
	{
		PERSPECTIVE = 1,
		ORTHOGRAPHIC = 2
	};
protected:
	uint	m_visibility; //可见分组
	uint	m_priority; //优先级，多个摄像机时 优先级值越大的最后渲染，也就显示在最上层
	fMat4	m_matProjection;
	fMat4	m_matView;
	fMat4	m_matViewProjection;
	fVec3   m_up;

	Camera::Type	m_type;
	float m_fieldOfView;
	float m_zoom[2];
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;

	bool m_projectDirty;
	bool m_viewDirty;
	bool m_frusumDirty;

	Camera();
	virtual ~Camera();
public:


	static Camera* createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
	static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	static Camera* createDefault(bool camera3d);

	bool initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	bool initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
	bool initDefault(bool camera3d);
	bool isCameraVisible(uint group);
	void setMask(uint mask);
	void addGroup(uint mask);
	virtual void setPosition(float x, float y, float z) override;
	virtual void setRotation(float x, float y, float z) override;

	const fMat4& getViewProjectMatrix();
};

#endif//__2022_03_18_CAMERA_H__
