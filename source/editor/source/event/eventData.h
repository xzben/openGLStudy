#pragma once
#include "eventid.h"
#include "define.h"

BEGIN_OGS_NAMESPACE
class Node;
END_OGS_NAMESPACE

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

struct EventEditor : public EventData
{
	EventEditor(OGS::Node* n, EditorEditorEvent e) : EventData(0), node(n), evt(e) {}

	OGS::Node* node;
	EditorEditorEvent evt;
};
END_EDITOR_NAMESPACE