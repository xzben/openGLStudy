#ifndef __NODE_2021_12_29_H__
#define __NODE_2021_12_29_H__

#include <vector>
#include "base/Object.h"
#include "common.h"
#include "math/math.h"
#include "render/Color.h"

BEGIN_NAMESPACE

class Component;

class Node : public Object
{
protected:
	std::vector<Node*> m_childrens;
	std::vector<Component*> m_components;
	
	POSITION m_pos;
	fVec3 m_scale;
	fVec3 m_rotation;
	Color m_color;
	Color m_parentColor;
	Color m_drawColor;

	bool m_dirtyMat;
	
	fMat4 m_localMat;  //节点本地坐标系的变换
	fMat4 m_matModel;  //节点从父节点一直继承下来的变换

	Node* m_parent;
	bool m_running;
	bool m_pause;
	uint m_groupmask;
	std::string m_name;
	int m_tag;
protected:
	friend class Shader;
	const fMat4& getShaderModel();
	virtual const Color& getDrawColor() { return m_drawColor; }

	bool updateSelfModelMat();
	void updateWorlModelMat(const fMat4& parentTrans, bool parentDirty);
	void updateDrawColor(const Color& parentColor);
	void getParentTrnasparent(fMat4& transparent);
protected:
	virtual void doLoad();  //构造对象完毕就会执行
	virtual void doStart();  //所在scene切入渲染开始触发
	virtual void doPause();
	virtual void doResume();
	virtual void doStop();
	virtual void doDestroy();
	virtual void doUpdate(float dt);
public:
	CREATE_FUNC(Node);
	 Node();
	 virtual ~Node();

	 void setTag(int tag) { m_tag = tag; }
	 int getTag() { return m_tag; }
	 void setName(const std::string& name) { m_name = name; }
	 const std::string& getName() { return m_name; }

	 Node* getChildByName(const std::string& name);
	 Node* getChildByTag(int tag);

	 void setColor(Color& color);
	 void setColor(Color&& color);
	 const Color& getColor() { return m_color; }
	 void setPosition(POSITION& pos);
	 virtual void setPosition(float x, float y, float z);
	 void setPositionX(float x);
	 void setPositionY(float y);
	 void setPositionZ(float z);
	 virtual void setRotation(const fVec3& rot);
	 POSITION getWorldPosition();
	 virtual void setRotation(float x, float y, float z);
	 virtual void setRotationX(float x);
	 virtual void setRotationY(float y);
	 virtual void setRotationZ(float z);
	 virtual void setScale(const fVec3& scale);
	 virtual void setScale(float x, float y, float z);
	 virtual void setScaleX(float x);
	 virtual void setScaleY(float y);
	 virtual void setScaleZ(float z);
	 virtual void setScale(float sclae);

	 const POSITION& getPosition();
	 float getPositionX();
	 float getPositionY();
	 float getPositionZ();

	 const fVec3& getRotation();
	 float getRotationX();
	 float getRotationY();
	 float getRotationZ();

	 const fVec3& getScale();
	 float getScaleX();
	 float getScaleY();
	 float getScaleZ();

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
	virtual POSITION convertToWorldSpace(const POSITION& localpos);
	virtual POSITION convertToNodeSpace(const POSITION& worldpos);
};

END_NAMESPACE

#endif // !__NODE_2021_12_29_H__
