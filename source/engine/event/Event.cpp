#include "Event.h"

Event::Event(EventType type)
	:m_stop(false)
	, m_type(type)
{

}

Event::~Event() {

}

EventTouch::EventTouch(float x, float y)
	:Event(EventType::TOUCH),
	x(x),
	y(y)
{

}

EventKeyboard::EventKeyboard(int key)
	:Event(EventType::KEYBOARD),
	key(key)
{

}

EventCustom::EventCustom(ListenerID listenerId, void* customData)
	:Event(EventType::CUSTOM),
	m_listenerId(listenerId),
	customData(customData)
{

}

EventListener::EventListener(EventType type, CALLFUNC func)
	:EventListener(type, "", func)
{

}


EventListener::EventListener(EventType type, ListenerID Id, CALLFUNC func)
	:type(type)
	,callback(func)
	,listenerId(Id)
{

}

EventListener::~EventListener() 
{

}