#include "Event.h"

BEGIN_NAMESPACE

Event::Event(EventType type)
	:m_stop(false)
	, m_type(type)
{

}

Event::~Event() {

}

EventTouch::EventTouch(TouchStatus status, const fVec2& pos)
	:Event(EventType::TOUCH)
	, status(status)
	, pos(pos)
{

}

EventKeyboard::EventKeyboard(int key)
	:Event(EventType::KEYBOARD),
	key(key)
{

}


EventMouse::EventMouse(int key, bool press)
	:Event(EventType::MOUSE)
	, key(key)
	, press(press)
{

}
EventMouse::~EventMouse()
{

}

EventCustom::EventCustom(ListenerID listenerId, void* customData)
	:Event(EventType::CUSTOM),
	listenerId(listenerId),
	customData(customData)
{

}

EventListener::EventListener(EventType type, const CALLFUNC& func)
	:EventListener(type, "", func)
{

}


EventListener::EventListener(EventType type, ListenerID Id, const CALLFUNC& func)
	: type(type)
	, callback(func)
	, listenerId(Id)
	, m_register(false)
	, m_enable(false)
	, m_order(0)
{

}

EventListener::~EventListener() 
{

}

void EventListener::doCall(Event* event) 
{
	this->callback(event);
}

END_NAMESPACE