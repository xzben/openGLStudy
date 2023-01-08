#pragma once

#include "core/base/Node.h"
#include "core/math/Rect.h"
BEGIN_OGS_NAMESPACE

class CameraComponent;
class Transform;

class Camera : public Node 
{
	DECLARE_CLASS(Camera)
	DECLARE_REFLEX_CLASS_FIELD(Camera)
public:
	static Camera* createDefault3DCamera();
	static Camera* createDefault2DCamera();

	Camera();
	virtual ~Camera();

	void setPerspective();
	void setOrtho();
	void setViewport(const Rect& rect);

	CameraComponent* getCameraCom() { return m_cameraCom; }
private:
	Transform* m_transform;
	CameraComponent* m_cameraCom;
};
END_OGS_NAMESPACE