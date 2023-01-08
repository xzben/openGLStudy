#include "Transform.h"

BEGIN_OGS_NAMESPACE
IMPLEMENT_CLASS(Transform)

BEGIN_REFLEX_CLASS_FIELD(Transform)
REFLEX_FIELD_NAME(Vector3, m_pos, "position")
REFLEX_FIELD_NAME(Vector3, m_rotation, "rotation")
REFLEX_FIELD_NAME(Vector3, m_scale, "scale")
END_REFLEX_CLASS_FIELD()

Transform::Transform()
{
	
}

END_OGS_NAMESPACE