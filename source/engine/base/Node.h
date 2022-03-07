#ifndef __NODE_2021_12_29_H__
#define __NODE_2021_12_29_H__

#include <vector>
#include "base/Object.h"
#include "common.h"

class Component;

class Node : Object
{
private:
	CREATE_FUNC(Node);

	std::vector<Node*> m_childrens;
	std::vector<Component*> m_components;
	POSITION m_pos;
	Node* m_parent;
	bool m_start;
	bool m_pause;
protected:
	void doLoad();  //构造对象完毕就会执行
	void doStart();  //所在scene切入渲染开始触发
	void doPause();
	void doResume();
	void doStop();
	void doDestroy();
	void doUpdate(float dt);
public:
	 Node();
	 virtual ~Node();

	Component* addComponent(Component* com);

	template<typename ComType>
	ComType* getComponent()
	{
		for (auto it = m_components.begin(); it != m_components.end() ; it++)
		{
			ComType* com = dynamic_cast<ComType*>(*it);

			if (com != nullptr)
			{
				return com;
			}
		}
	}

	template<typename ComType>
	ComType* addComponent()
	{
		return  dynamic_cast<ComType*>(this->addComponent(new ComType()));
	}

	void setParent(Node* node);
	void removeFromParent();

	void removeChild(Node* node);
	void addChild(Node* node);
	
	virtual void onLoad() {};
	virtual void start() {};
	virtual void onPause() {};
	virtual void onResume() {};
	virtual void stop() {};
	virtual void onDestroy() {};
	virtual void update(float dt) {};
};
#endif // !__NODE_2021_12_29_H__
