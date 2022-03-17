#ifndef __NODE_2021_12_29_H__
#define __NODE_2021_12_29_H__

#include <vector>
#include "base/Object.h"
#include "common.h"
#include "math/math.h"

class Component;

class Node : Object
{
protected:
	std::vector<Node*> m_childrens;
	std::vector<Component*> m_components;
	
	POSITION m_pos;
	fVec3 m_scale;
	fVec3 m_rotation;

	fMat4 m_matModel;  //节点的模型矩阵

	Node* m_parent;
	bool m_start;
	bool m_pause;
protected:
	friend class Shader;
	const fMat4& getShaderModel() { return m_matModel; }
protected:
	void doLoad();  //构造对象完毕就会执行
	void doStart();  //所在scene切入渲染开始触发
	void doPause();
	void doResume();
	void doStop();
	void doDestroy();
	void doUpdate(float dt);
public:
	CREATE_FUNC(Node);
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
