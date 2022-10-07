#include "Node.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Node)
IMPLEMENT_REFLEX_CLASS_BASE(Node)

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

Component* Node::getComponet(const std::string& name)
{
	for (auto com : m_components)
	{
		if (com->GetRuntime()->getName() == name)
		{
			return com;
		}
	}

	return nullptr;
}

std::vector<Component*> Node::getComponents(const std::string& name)
{
	std::vector<Component*> rets;
	for (auto com : m_components)
	{
		if (com->GetRuntime()->getName() == name)
		{
			rets.push_back(com);
		}
	}

	return rets;
}
END_OGS_NAMESPACE