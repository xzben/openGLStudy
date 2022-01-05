#include "Node.h"
#include "base/Component.h"

Node::Node()
	: m_parent(nullptr)
	, m_start(false)
	, m_pause(false)
{

}

Node::~Node() 
{
	this->doPause();
	this->doStop();
	this->doDestroy();
}


Component* Node::addComponent(Component* com)
{
	this->m_components.push_back(com);
	com->setOwner(this);
	return com;
}

void Node::setParent(Node* node) 
{
	this->m_parent = node;
}

void Node::addChild(Node* node)
{
	node->setParent(this);
	node->addRef();
	this->m_childrens.push_back(node);
	if (this->m_start) {
		node->doStart();
	}
}

void Node::removeChild(Node* node)
{
	if (node->m_parent != this) return;

	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor--)
	{
		if (node == *itor) {
			this->m_childrens.erase(itor);
			node->delRef();
			node->m_parent = nullptr;
			break;
		}
	}
}

void Node::removeFromParent()
{
	if (this->m_parent != nullptr) {
		this->m_parent->removeChild(this);
	}
}

void Node::doLoad()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doLoad();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doLoad();
	}
	this->onLoad();
}

void Node::doStart()
{
	m_start = true;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doStart();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doStart();
	}

	this->start();
}


void Node::doResume()
{
	m_pause = false;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doResume();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doResume();
	}

	this->onResume();
}

void Node::doPause()
{
	m_pause = true;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doPause();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doPause();
	}

	this->onPause();
}

void Node::doStop()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doStop();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doStop();
	}
	this->stop();
	m_start = false;
}

void Node::doDestroy()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doDestroy();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doDestroy();
	}

	this->onDestroy();
}

void Node::doUpdate(float dt)
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doUpdate(dt);
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doUpdate(dt);
	}

	this->update(dt);
}