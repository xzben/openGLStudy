#pragma once

#include <vector>
#include <string>
#include "Object.h"

BEGIN_OGS_NAMESPACE

class Component;

class Node : public Object
{
public:
	void addComponent(const Component* com);

	template<typename T, typename ...Args>
	void newComponent(std::string& name, Args&& ...args);

	template<typename T>
	T* getComponent();

protected:
	std::vector<Component*> m_components;
};

template<typename T, typename ...Args>
void Node::newComponent(std::string& name, Args&& ...args)
{
	auto com = new T(...args);
	this->addComponent(com);
}

template<typename T>
T* Node::getComponent()
{
	for (auto com : m_components)
	{
		T* ptr = dynamic_cast<T>(com);
		if (ptr != nullptr)
		{
			return ptr;
		}
	}

	return nullptr;
}

END_OGS_NAMESPACE