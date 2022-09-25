#include "Node.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Node)

BEGIN_REFLEX_CLASS_FIELD(Node)
REFLEX_FIELD(std::string, Node::m_name)
END_REFLEX_CLASS_FIELD()

END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE

void Node::setParent(Node* parent)
{
	if (m_parent)
	{
		m_parent->removeChild(this);
	}

	if (parent)
	{
		parent->addChild(this);
	}
	
	m_parent = parent;
}

Node* Node::getParent()
{
	return m_parent;
}

END_OGS_NAMESPACE