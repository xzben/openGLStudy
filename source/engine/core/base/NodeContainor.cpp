#include "NodeContainor.h"
#include "Node.h"
BEGIN_OGS_NAMESPACE

NodeContainor::NodeContainor()
{

}

void NodeContainor::addChild(Node* node)
{
	m_childrens.push_back(node);
}

void NodeContainor::removeChild(Node* node)
{
	for (auto itor = m_childrens.begin(); itor != m_childrens.end(); itor++)
	{
		if (*itor == node)
		{
			m_childrens.erase(itor);
			break;
		}
	}
}

Node* NodeContainor::getChildByName(const std::string& name)
{
	for (auto child : m_childrens)
	{
		if (child->getName() == name)
		{
			return child;
		}
	}

	return nullptr;
}

void NodeContainor::foreach(std::function<bool(Node*)> func)
{
	for (auto child : m_childrens)
	{
		if (!func(child))
		{
			break;
		}
	}
}
END_OGS_NAMESPACE