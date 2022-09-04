#pragma once
#include "editor_define.h"

BEGIN_EDITOR_NAMESPACE

enum EditorEvent
{
	MENU,
	FRAME,
};

using EditorSubEvent = unsigned int;

enum EditorMenuEvent
{
	MENU_CLICK,
	MENU_CHECKED,
	MENU_UNCHECKED,
};

enum EditorFrameEvent
{
	FRAME_OPEN,
	FRAME_CLOSE,
};

END_EDITOR_NAMESPACE