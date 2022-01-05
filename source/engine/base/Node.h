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
	Node* m_parent;
	bool m_start;
	bool m_pause;
protected:
	void doLoad();
	void doStart();
	void doPause();
	void doResume();
	void doStop();
	void doDestroy();
	void doUpdate(float dt);
public:
	 Node();
	 virtual ~Node();

	Component* addComponent(Component* com);

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
