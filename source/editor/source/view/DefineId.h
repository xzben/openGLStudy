#pragma once

#include "editor_define.h"

BEGIN_EDITOR_NAMESPACE

enum IDMainMenu : unsigned int
{
	LINE = 0,
	File = 1,
	FILE_EXIT,

	Edit = 100,
	View = 200,
	Help = 300,

	Window = 10000,
};

enum IDMainFrame : unsigned short
{
	NODE_TREE = 1,
	ASSET_VIEW,
	GAME_VIEW,
	SCENE_VIEW,
	CONSOLE_VIEW,
	INSPECTOR_VIEW,
	ATTR_VIEW_2,
};

enum MainDockSpace : unsigned char
{
	EMPTY = 0,
	LEFT_TOP,
	LEFT_BOTTOM,
	CENTER_TOP,
	CENTER_BOTTOM,
	RIGHT,
};

END_EDITOR_NAMESPACE
