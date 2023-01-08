#pragma once

#include "Object.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class Node;

class Component : public Object
{
	DECLARE_CLASS(Component);
	DECLARE_REFLEX_CLASS_FIELD(Component)
	friend class Node;
public:
	Component() = default;
	virtual ~Component() = default;

	void setNode(Node* node) { m_node = node; }
	void setEnable(bool enable);
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
	void doLoad();
	void doDisable();
	void doEnable();
	void doStart();
	void doStop();
	void doUnload();

	virtual void onLoad() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUnload() {}
	virtual void onStart() {}
	virtual void onStop() {}
protected:
	Node* m_node = nullptr;
	bool m_enable{ true };
};

END_OGS_NAMESPACE