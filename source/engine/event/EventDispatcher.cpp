#include "EventDispatcher.h"
#include <algorithm>

BEGIN_NAMESPACE

EventDispatcher::EventDispatcher()
{

}

EventDispatcher::~EventDispatcher()
{

}

void EventDispatcher::sortListeners(EventListenerArray* arr)
{
	if (arr == nullptr) return;

	std::sort(arr->begin(), arr->end(), [](EventListener* a, EventListener* b){
		return a->getOrder() > b->getOrder();
	});
}

EventListenerArray* EventDispatcher::getEventListeners(const EventType& type, bool autoCreate /*= false*/)
{
	auto itor = this->m_events.find(type);

	if (itor == this->m_events.end()) 
	{
		if (autoCreate)
		{
			auto arry = new EventListenerArray();
			this->m_events.insert(std::pair<EventType, EventListenerArray*>(type, arry));

			return arry;
		}
		else
		{
			return nullptr;
		}
	}

	return itor->second;
}


void EventDispatcher::addEventListener(const EventType& type, EventListener* listener)
{
	auto arr = this->getEventListeners(type, true);
	arr->push_back(listener);
	EventDispatcher::sortListeners(arr);
}

void EventDispatcher::removeEventListener(EventListener* listener)
{
	EventType type = listener->type;
	EventListenerArray* arr = nullptr;

	if (type == EventType::CUSTOM) 
	{
		ListenerID id = listener->getListenerId();
		arr = getCustomEventListeners(id, false);
	}
	else
	{
		arr = this->getEventListeners(type, false);
	}

	for (auto it = arr->begin(); it != arr->end(); it++)
	{
		if (*it == listener) {
			arr->erase(it);
			break;
		}
	}
}

EventListenerArray* EventDispatcher::getCustomEventListeners(const ListenerID& id, bool autoCreate /*= false*/)
{
	auto itor = this->m_customEvents.find(id);

	if (itor == this->m_customEvents.end())
	{
		if (autoCreate)
		{
			auto arry = new EventListenerArray();
			this->m_customEvents.insert(std::pair<ListenerID, EventListenerArray*>(id, arry));

			return arry;
		}
		else
		{
			return nullptr;
		}

	}

	return itor->second;
}

void EventDispatcher::addCustomListener(ListenerID id, EventListener* listener)
{
	listener->setListenerId(id);

	EventListenerArray* arr = this->getCustomEventListeners(id, true);
	
	if (nullptr != arr) {
		arr->push_back(listener);
		EventDispatcher::sortListeners(arr);
	}
}

void EventDispatcher::addKeyboardListener(EventListener* listener)
{
	this->addEventListener(EventType::KEYBOARD, listener);
}

void EventDispatcher::addMouseListener(EventListener* listener)
{
	this->addEventListener(EventType::MOUSE, listener);
}

void EventDispatcher::addTouchListener(EventListener* listener)
{
	this->addEventListener(EventType::TOUCH, listener);
}

void EventDispatcher::dispatchEvent(Event* event)
{
	auto arr = this->getEventListeners(event->getType());
	if (arr == nullptr) return;

	for (auto itor = arr->begin(); itor != arr->end(); itor++) 
	{
		(*itor)->doCall(event);
	}
}

void EventDispatcher::dispatchTouch(EventTouch* event)
{
	this->dispatchEvent(event);
}
void EventDispatcher::dispatchKeyboard(EventKeyboard* event)
{
	this->dispatchEvent(event);
}
void EventDispatcher::dispatchMouse(EventMouse* event)
{
	this->dispatchEvent(event);
}
void EventDispatcher::dispatchCustomEvent(EventCustom* event)
{
	auto id = event->listenerId;
	auto itor = this->m_customEvents.find(id);
	EventListenerArray* arr = nullptr;


	if (itor != this->m_customEvents.end())
	{
		arr = itor->second;
	}

	if (arr == nullptr) return;

	for (auto it = arr->begin(); it != arr->end(); it++)
	{
		(*it)->doCall(event);
	}
}

END_NAMESPACE