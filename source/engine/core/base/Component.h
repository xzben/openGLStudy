#pragma once

#include "Object.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class Node;

class Component : public Object
{
	DECLARE_CLASS(Component);
	DECLARE_REFLEX_CLASS_FIELD(Component)
public:
	Component() = default;
	virtual ~Component() = default;

	void setNode(Node* node) { m_node = node; }
	void setEnable(bool enable) { m_enable = enable; }
	bool isEnable();

	template<typename T>
	T* getComponet()
	{
		if (this->m_node)
		{
			return this->m_node->getComponent<T>();
		}
		return nullptr;
	}

protected:
	Node* m_node = nullptr;
	bool m_enable{ true };
};

END_OGS_NAMESPACE