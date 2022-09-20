#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "math/math.h"

BEGIN_OGS_NAMESPACE

class Transform : public Component
{
public:
	Transform();

	void setPosition(Position&& pos) { m_pos = pos; }
	void setRotation(Rotation&& rot) { m_rotation = rot; }
	void setScale(Scale&& scale) { m_scale = scale; }
	const Position& getPosition() { return m_pos; }
	const Rotation& getRotation() { return m_rotation; }
	const Scale& getScale() { return m_scale; }
private:
	Position m_pos{0,0,0};
	Rotation m_rotation{0,0,0};
	Scale    m_scale{1,1,1};
};

END_OGS_NAMESPACE