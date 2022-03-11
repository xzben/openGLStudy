#ifndef __2022_03_08_EVENT_H__
#define __2022_03_08_EVENT_H__

#include <functional>
#include <string>

typedef std::string ListenerID;


enum class EventType
{
	UNKONW = 0,
	TOUCH,  //�����¼�
	KEYBOARD, //�����¼�
	MOUSE, //����¼�
	CUSTOM = 100, //�Զ����¼�
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
};

class EventTouch : public Event
{
public:
	float x, y;
public:
	EventTouch(float x, float y);
	virtual ~EventTouch() {};
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
	ListenerID m_listenerId;
	void* customData;

public:
	EventCustom(ListenerID listenerId, void* customData = nullptr);
	virtual ~EventCustom() {};
};

class EventListener
{
public:
	typedef  std::function<void(Event*)> CALLFUNC;
	EventType	type = EventType::UNKONW;
	ListenerID	listenerId;
	CALLFUNC	callback;

	bool		m_register;  //�Ƿ�������¼��ɷ�����
	bool		m_enable;
	int			m_order; //���ȼ�

	EventListener(EventType type, CALLFUNC func);
	EventListener(EventType type, ListenerID Id, CALLFUNC func);
	virtual ~EventListener();
};

#endif//__2022_03_08_EVENT_H__