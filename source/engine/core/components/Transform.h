#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "core/math/math.h"

BEGIN_OGS_NAMESPACE

class Transform : public Component
{
	DECLARE_CLASS(Transform)
	DECLARE_REFLEX_CLASS_FIELD(Transform)

	friend class CameraComponent;
public:
	Transform();

	void setPosition(Vector3& pos) { m_pos = pos; }
	void setRotation(Quaterion& rot) { m_rotation = rot; }
	void setScale(Vector3& scale) { m_scale = scale; }
	const Vector3& getPosition() { return m_pos; }
	const Quaterion& getRotation() { return m_rotation; }
	const Vector3& getScale() { return m_scale; }
protected:
	void dirtyMatrix();
protected:
	Vector3 m_pos{0,0,0};
	Quaterion m_rotation;
	Vector3 m_scale{1,1,1};
	Matrix4  m_matrixModel; //model æÿ’Û
};

END_OGS_NAMESPACE