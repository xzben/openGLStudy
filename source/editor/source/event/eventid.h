#pragma once
#include "editor_define.h"

BEGIN_EDITOR_NAMESPACE

//�¼�������
enum EditorEvent
{
	MENU,  //�˵��¼�
	FRAME, //�����¼�
	Editor, //�༭�¼�
};

//��Ӧÿ�����¼������е�С����
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
	CHANGE_EDITOR_NODE, //nodetree �༭��node
	CHANGE_ACTIVE_NODE, // nodetree ѡ�е�node
};

END_EDITOR_NAMESPACE