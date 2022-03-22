#ifndef __2022_01_06_EVENT_DISPATCHER_H__
#define __2022_01_06_EVENT_DISPATCHER_H__

#include <map>

#include <unordered_map>
#include "common.h"
#include "event/Event.h"

BEGIN_NAMESPACE

class Object;

typedef std::vector<EventListener*> EventListenerArray;
class EventDispatcher
{
protected:
	std::unordered_map<EventType, EventListenerArray*> m_events;
	std::unordered_map<ListenerID, EventListenerArray*> m_customEvents;
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	EventListenerArray* getEventListeners(const EventType& type);
	static void sortListeners(EventListenerArray* arr);

	void addEventListener(const EventType& type, EventListener* listener);

	void addTouchListener(EventListener* listener);
	void addKeyboardListener(EventListener* listener);
	void addMouseListener(EventListener* listener);
	void addCustomListener(ListenerID id, EventListener* listener);
	
	void dispatchEvent(Event* event);
	void dispatchTouch(EventTouch* event);
	void dispatchKeyboard(EventKeyboard* event);
	void dispatchMouse(EventMouse* event);
	void dispatchCustomEvent(EventCustom* event);
};

END_NAMESPACE

#endif//__2022_01_06_EVENT_DISPATCHER_H__