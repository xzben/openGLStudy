#pragma once
#include "eventid.h"

BEGIN_EDITOR_NAMESPACE

struct EventData
{
	int sourceId{ 0 };

	EventData(int id):sourceId(id){}
};

struct EventDataMenu : public EventData
{
	EventDataMenu(int id,EditorMenuEvent e) :EventData(id), evt(e) {}
	EditorMenuEvent evt;
};

struct EventDataFrame : public EventData
{
	EventDataFrame(int id, EditorFrameEvent e) : EventData(id), evt(e) {}
	EditorFrameEvent evt;
};

END_EDITOR_NAMESPACE