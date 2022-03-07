#ifndef __2022_01_06_EVENT_DISPATCHER_H__
#define __2022_01_06_EVENT_DISPATCHER_H__

#include <map>
#include "common.h"

typedef void (*EVENT_CALLBACK)(void*, ...);

class Object;

typedef std::string EventKey;


class EventItem
{
private:
	Object* m_obj;
	EventKey m_event;
	EVENT_CALLBACK m_callback;
	bool m_pause;
	bool m_valid;
	int count;
	int order;
};

class EventDispatcher
{
public:
	std::map<EventKey, std::vector<EventItem>> m_event2Events;
	std::map<Object*, std::vector<EventItem>>  m_obj2Events;

public:
	void addListener(EventKey evt, EVENT_CALLBACK callfunc, Object* owner = nullptr, int count = -1, int order = 0);
	void addListenerOnce(EventKey evt, EVENT_CALLBACK callfunc, Object* owner, int order = 0);
	void removeListener(EventKey evt, EVENT_CALLBACK callfunc, Object* owner = nullptr);
	void removeListener(Object* obj);
	void clearListener();
};

#endif//__2022_01_06_EVENT_DISPATCHER_H__