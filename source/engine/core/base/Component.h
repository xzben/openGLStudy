#pragma once

#include "Ref.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class Node;

class Component : public Ref
{
	DECLARE_CLASS(Component);
public:
	Component() = default;
	virtual ~Component() = default;

	void setNode(Node* node) { m_node = node; }
	
	template<typename T>
	T* getComponet();

protected:
	Node* m_node = nullptr;
};

template<typename T>
T* Component::getComponet()
{
	if (this->m_node)
	{
		return this->m_node->getComponent<T>();
	}

	return nullptr;
}

END_OGS_NAMESPACE