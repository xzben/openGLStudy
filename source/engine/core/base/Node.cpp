#include "Node.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(Node)
IMPLEMENT_REFLEX_CLASS_BASE(Node)

BEGIN_REFLEX_CLASS_FIELD(Node)
REFLEX_FIELD(std::string, Node::m_name)
END_REFLEX_CLASS_FIELD()

END_OGS_NAMESPACE

BEGIN_OGS_NAMESPACE

Node::~Node()
{
	doStop();
	doUnload(); //析构的时候强制unload 一次
}

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
	if (m_parent->isRunning())
	{
		doStart();
	}
}

void Node::handleInit()
{
	doLoad();
}

Node* Node::getParent()
{
	return m_parent;
}

void Node::setActive(bool active)
{
	if (active == m_active) return;
	active ? doEnable() : doDisable();
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

void Node::doLoad()
{
	if (m_loaded) return;
	m_loaded = true;
	for (auto &com : m_components)
	{
		com->doLoad();
	}
	onLoad();
	for (auto& child : m_childrens)
	{
		child->doLoad();
	}
}
void Node::doDisable()
{
	if (!m_active) return;
	m_active = false;
	for (auto& com : m_components)
	{
		com->doDisable();
	}
	onDisable();
	for (auto& child : m_childrens)
	{
		child->doDisable();
	}
}

void Node::doEnable()
{
	if (m_active) return;
	m_active = true;
	for (auto& com : m_components)
	{
		com->doEnable();
	}
	onEnable();
	for (auto& child : m_childrens)
	{
		child->doEnable();
	}
}
void Node::doStart()
{
	if (m_running) return;
	m_running = true;
	for (auto& com : m_components)
	{
		com->doStart();
	}
	onStart();
	for (auto& child : m_childrens)
	{
		child->doStart();
	}
}

void Node::doStop()
{
	if (!m_running) return;
	m_running = false;
	for (auto& com : m_components)
	{
		com->doStop();
	}
	onStop();
	for (auto& child : m_childrens)
	{
		child->doStop();
	}
}

void Node::doUnload()
{
	if (!m_loaded) return;
	m_loaded = false;
	for (auto& com : m_components)
	{
		com->doUnload();
	}
	onUnload();
	for (auto& child : m_childrens)
	{
		child->doUnload();
	}
}
END_OGS_NAMESPACE