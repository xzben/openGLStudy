#include "EditorEventMgr.h"

BEGIN_EDITOR_NAMESPACE

AutoRef<EventNotify>& EditorEventMgr::getNotifybyEvent(EditorEvent event)
{
	auto it = m_events.find(event);
	
	if (it == m_events.end())
	{
		EventNotify* notify = new EventNotify();
		it = m_events.insert(std::make_pair(event, notify)).first;
	}
	
	return it->second;
}

AutoRef<EventNotify>& EditorEventMgr::getNotifybyEventAndId(EditorEvent event, int id)
{
	auto itmap = m_eventIdEvent.find(event);
	if (itmap == m_eventIdEvent.end())
	{
		itmap = m_eventIdEvent.insert(std::make_pair(event, std::unordered_map<int, AutoRef<EventNotify>> {})).first;
	}

	auto idnotify = itmap->second.find(id);
	if (idnotify == itmap->second.end())
	{
		idnotify = itmap->second.insert(std::make_pair(id, new EventNotify)).first;
	}

	return idnotify->second;
}

void EditorEventMgr::emitEvent(EditorEvent event, EventData* data)
{
	if (data == nullptr) return;

	getNotifybyEvent(event)->emit(data);
	getNotifybyEventAndId(event, data->sourceId)->emit(data);
}

END_EDITOR_NAMESPACE