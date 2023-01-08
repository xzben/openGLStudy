#pragma once

#include <vector>
#include <string>
#include "Object.h"
#include "Component.h"
#include "NodeContainor.h"
#include "core/base/Flag.h"

BEGIN_OGS_NAMESPACE

class Component;

class Node : public NodeContainor,  public Object
{
	DECLARE_CLASS(Node)
	DECLARE_REFLEX_CLASS_FIELD(Node)
public:
	friend class RenderSystem;

	virtual ~Node();
	void setName(const std::string& name) { m_name = name; }
	const std::string& getName() { return m_name; }
	void setActive(bool active);
	bool isActive() { return m_active; }
	bool isRunning() { return m_running; }
	void setParent(Node* parent);
	virtual void handleInit() override;
	Node* getParent();

	Component* addComponent(Component* com)
	{
		if (com == nullptr) return nullptr;
		com->setNode(this);
		m_components.push_back(com);
		return com;
	}

	template<typename T, typename ...Args>
	T* addComponent(Args&& ...args)
	{
		auto com = new T(args...);
		this->addComponent(com);

		return com;
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

	Component* getComponet(const std::string& name);
	std::vector<Component*> getComponents(const std::string& name);

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
	void doLoad();		// 节点加载
	void doDisable();	// 节点 设置 acvite false
	void doEnable();	// 节点设置 active true
	void doStart();		// 节点进入渲染场景
	void doStop();		// 节点离开渲染场景
	void doUnload();    // 节点卸载

	virtual void onLoad() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUnload() {}
	virtual void onStart(){}
	virtual void onStop(){}
protected:
	std::vector<Component*> m_components;
	std::string m_name{"Node"};
	Flag32 m_visibility;
	Node* m_parent{nullptr};
	bool m_loaded{ false };
	bool m_active{true};
	bool m_running{ false };
};

END_OGS_NAMESPACE