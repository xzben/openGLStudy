#pragma once
#include "editor_define.h"

BEGIN_EDITOR_NAMESPACE

//事件大类型
enum EditorEvent
{
	MENU,  //菜单事件
	FRAME, //窗口事件
	Editor, //编辑事件
};

//对应每个大事件类型中的小类型
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

enum EditorEditorEvent
{
	CHANGE_EDITOR_NODE, //nodetree 编辑的node
	CHANGE_ACTIVE_NODE, // nodetree 选中的node
};

END_EDITOR_NAMESPACE