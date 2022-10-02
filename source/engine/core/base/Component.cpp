#include "Component.h"
#include "Node.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Component)
IMPLEMENT_REFLEX_CLASS_BASE(Component)

BEGIN_REFLEX_CLASS_FIELD(Component)
REFLEX_FIELD(std::string, Component::m_name)
END_REFLEX_CLASS_FIELD()

END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE
bool Component::isEnable() 
{ 
	return m_enable && m_node->isActive(); 
}

END_OGS_NAMESPACE