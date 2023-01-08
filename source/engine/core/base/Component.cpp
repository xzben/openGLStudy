#include "Component.h"
#include "Node.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Component)
IMPLEMENT_REFLEX_CLASS_BASE(Component)

BEGIN_REFLEX_CLASS_FIELD(Component)
END_REFLEX_CLASS_FIELD()

END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE
bool Component::isEnable() 
{ 
	return m_enable && m_node->isActive(); 
}

void Component::setEnable(bool enable)
{ 
	if (enable == m_enable) return;

	m_enable = enable; 
	m_enable ? doEnable() : doDisable();
}

void Component::doLoad()
{
	onLoad();
}

void Component::doDisable()
{
	onDisable();
}

void Component::doEnable()
{
	onEnable();
}

void Component::doStart()
{
	onStart();
}

void Component::doStop()
{
	onStop();
}

void Component::doUnload()
{
	onUnload();
}

END_OGS_NAMESPACE