#ifndef __2022_03_08_EVENT_H__
#define __2022_03_08_EVENT_H__

#include <functional>
#include "common.h"
#include <string>
#include "math/Vec2.h"

BEGIN_NAMESPACE

typedef std::string ListenerID;


enum class EventType
{
	UNKONW = 0,
	TOUCH,  //触摸事件
	KEYBOARD, //键盘事件
	MOUSE, //鼠标事件

	CUSTOM = 100, //自定义事件
};

class Event
{
protected:
	EventType	m_type = EventType::UNKONW;
	bool		m_stop;
public:
	Event(EventType type);
	virtual ~Event();

	inline bool isStop() { return this->m_stop; }
	void stop() { this->m_stop = true; }
	EventType& getType() { return this->m_type;  }
};

class EventTouch : public Event
{
public:
	fVec2 pos;
	fVec2 prePos;
	TouchStatus status;
public:
	EventTouch(TouchStatus status, const fVec2& pos);
	virtual ~EventTouch() {};
	fVec2 getDeltaPos() { return pos - prePos; }
};

class EventKeyboard : public Event
{
public:
	int key;
public:
	EventKeyboard(int key);
	virtual ~EventKeyboard() {};
};

class EventCustom : public Event
{
public:
	ListenerID listenerId;
	void* customData;

public:
	EventCustom(ListenerID listenerId, void* customData = nullptr);
	virtual ~EventCustom() {};
};

class EventMouse : public Event
{
public:
	int key;
	bool press;

	EventMouse(int key, bool press);
	virtual ~EventMouse();
};
class EventListener
{
public:
	typedef  std::function<void(Event*)> CALLFUNC;
	EventType	type = EventType::UNKONW;
	ListenerID	listenerId;
	CALLFUNC	callback;

	bool		m_register;  //是否加入了事件派发起中
	bool		m_enable;
	int			m_order; //优先级

	EventListener(EventType type, const CALLFUNC& func);
	EventListener(EventType type, ListenerID Id, const CALLFUNC& func);
	virtual ~EventListener();


	void setOrder(const int order) { m_order = order; }
	void setEnable(const bool enable) { m_enable = enable; }
	void setRegister(const bool reg) { m_register = reg;  }

	void setListenerId(const ListenerID id) { listenerId = id; }

	const ListenerID& getListenerId() { return listenerId; }
	int  getOrder() { return m_order; }
	bool isEnable() { return m_enable; }
	bool isRegister() { return m_register; }

	void doCall(Event* event);
};

END_NAMESPACE

#endif//__2022_03_08_EVENT_H__