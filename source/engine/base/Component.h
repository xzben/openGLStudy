#ifndef __2021_12_29_COMPONENT_H__
#define __2021_12_29_COMPONENT_H__

#include "base/Object.h"
#include "math/Mat4.h"

BEGIN_NAMESPACE

class Node;

class Component : Object
{
public:
	enum class Status {
		ENABLE = 0,
		VISIBLE = 1,

		MAX_BIT = 32,
		
	};
protected:
	friend class Node;

	std::string m_name;
	Node* m_node;
	bool m_enable;
	int  m_status;
	Component();
	virtual ~Component();
	void setOwner(Node* node);
	void setName( const std::string& name) { m_name = name; }
	const std::string& getComName() { return m_name; };

	void setStatusBit(bool enable, Status status);
	bool getStatusBit(Status status);
public:
	void setEnable(bool enable);
	bool isEnable();
	float getLastDt();
	float getLastTime();
	Node* getNode() { return m_node; }
protected:
	void doLoad();
	void doStart();
	void doResume();
	void doPause();
	void doStop();
	void doDestroy();
	void doUpdate(float dt);
public:
	virtual void update(float dt) {};
	virtual void onLoad() {};
	virtual void start() {};
	virtual void onPause() {};
	virtual void onResume() {};
	virtual void stop() {};
	virtual void onDestroy() {};
};

END_NAMESPACE

#endif//__2021_12_29_COMPONENT_H__