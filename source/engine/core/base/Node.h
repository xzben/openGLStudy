#pragma once

#include <vector>
#include <string>
#include "Object.h"
#include "Component.h"
#include "NodeContainor.h"
BEGIN_OGS_NAMESPACE

class Component;

class Node : public NodeContainor,  public Object
{
	DECLARE_CLASS(Node)
	DECLARE_REFLEX_CLASS_FIELD(Node)
public:
	void setName(const std::string&& name) { m_name = name; }
	const std::string& getName() { return m_name; }
	void setActive(bool active) { m_active = active; }
	bool isActive() { return m_active; }
	void setParent(Node* parent);
	Node* getParent();

	void addComponent(Component* com)
	{
		if (com == nullptr) return;
		com->setNode(this);
		m_components.push_back(com);
	}

	template<typename T, typename ...Args>
	void createComponent(Args&& ...args)
	{
		auto com = new T(args...);
		this->addComponent(com);
	}

	const std::vector<Component*>& getAllComponents() { return m_components; }

	template<typename T>
	T* getComponent()
	{
		for (auto com : m_components)
		{
			T* ptr = com->ToCast<T>();
			if (ptr)
			{
				return ptr;
			}
		}

		return nullptr;
	}


	template<typename T>
	std::vector<T*> getComponents()
	{
		std::vector<T*> rets;
		for (auto com : m_components)
		{
			T* ptr = com->ToCast<T>();
			if (ptr)
			{
				rets.push_back(ptr);
			}
		}

		return rets;
	}
protected:
	std::vector<Component*> m_components;
	std::string m_name{""};
	Node* m_parent{nullptr};
	bool m_active{true};
};

END_OGS_NAMESPACE