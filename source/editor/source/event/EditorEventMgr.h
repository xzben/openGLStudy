#pragma once

#include "editor_common.h"
#include "core/tool/Singleton.h"
#include "core/base/Notify.h"
#include "eventid.h"
#include "eventData.h"
#include <unordered_map>

BEGIN_EDITOR_NAMESPACE
using EventNotify = OGS::Notify<EventData*>;

class EditorEventMgr : public OGS::Singleton<EditorEventMgr>
{
public:
	EditorEventMgr() = default;
	virtual ~EditorEventMgr() {}
	AutoRef<EventNotify>& getNotifybyEvent(EditorEvent event);
	AutoRef<EventNotify>& getNotifybyEventAndId(EditorEvent event, int id);
	void emitEvent(EditorEvent event, EventData* data);
private:
	std::unordered_map<EditorEvent, AutoRef<EventNotify>>  m_events;
	std::unordered_map<EditorEvent, std::unordered_map<int, AutoRef<EventNotify>>> m_eventIdEvent;
};

END_EDITOR_NAMESPACE