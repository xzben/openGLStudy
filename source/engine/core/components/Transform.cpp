#include "Transform.h"

BEGIN_OGS_NAMESPACE
IMPLEMENT_CLASS(Transform)

BEGIN_REFLEX_CLASS_FIELD(Transform)
REFLEX_FIELD_NAME(Vector3, m_pos, "position")
REFLEX_FIELD_NAME(Vector3, m_rotation, "rotation")
REFLEX_FIELD_NAME(Vector3, m_scale, "scale")
REFLEX_FIELD_NAME(Color, m_colortest, "color")
REFLEX_FIELD_NAME(std::string, m_strtest, "string")
REFLEX_FIELD_NAME(float, m_floattest, "float")
REFLEX_FIELD_NAME(int, m_inttest, "int")
END_REFLEX_CLASS_FIELD()

Transform::Transform()
{
	
}

END_OGS_NAMESPACE