#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "core/math/math.h"

BEGIN_OGS_NAMESPACE

class Transform : public Component
{
	DECLARE_CLASS(Transform)
	DECLARE_REFLEX_CLASS_FIELD(Transform)
public:
	Transform();

	void setPosition(Vector3& pos) { m_pos = pos; }
	void setRotation(Vector3& rot) { m_rotation = rot; }
	void setScale(Vector3& scale) { m_scale = scale; }
	const Vector3& getPosition() { return m_pos; }
	const Vector3& getRotation() { return m_rotation; }
	const Vector3& getScale() { return m_scale; }
private:
	Vector3 m_pos{0,0,0};
	Vector3 m_rotation{0,0,0};
	Vector3 m_scale{1,1,1};
	Color   m_colortest{0.f, 0.f, 0.f, 255.f};
	std::string m_strtest{""};
	float    m_floattest{0};
	int      m_inttest{0};
};

END_OGS_NAMESPACE