#include "EditorWindow.h"
#include "EditorMenu.h"
#include "EditorMenuBar.h"
#include "DefineId.h"
#include "EditorFrame.h"
#include "event/EditorEventMgr.h"

BEGIN_EDITOR_NAMESPACE

struct MenuDefineItem
{
	IDMainMenu id;
	const char* name;
	const char* shortcuts;
	std::vector<MenuDefineItem> items;
};

static MenuDefineItem MainMenuConfig[] = {
	{ IDMainMenu::File, "File", nullptr,
		{
			{ IDMainMenu::FILE_EXIT, "Exit", "Alt+F4", {}},
		}
	},

	{IDMainMenu::Edit, "Edit", nullptr,
		{
		}
	},

	{IDMainMenu::Window, "Window", nullptr,
		{
		}
	},

	{IDMainMenu::View, "View", nullptr,
		{
		}
	},
	{IDMainMenu::Help, "Help", nullptr,
		{
		}
	},
};

static SharePtr<EditorMenu> CreateMenuByConfig(const MenuDefineItem& config)
{
	SharePtr<EditorMenu> menu = make_share(new EditorMenu(config.id, config.name, config.shortcuts == nullptr ? "" : config.shortcuts));

	for (auto sub : config.items)
	{
		SharePtr<EditorMenu> submenu = CreateMenuByConfig(sub);
		menu->addMenu(submenu);
	}

	return menu;
}

void EditorWindow::createFrameWindowSubMenu(int index, SharePtr<EditorFrame>& frame)
{
	IDMainMenu subid = IDMainMenu((int)IDMainMenu::Window + frame->getMainFrameId());
	SharePtr<EditorMenu> submenu = make_share(new EditorMenu(subid, frame->getTitle().c_str(), ""));
	submenu->setItemCheckable(true);
	submenu->setClickCallback([=](bool ischeck) {
		frame->setVisible(ischeck);
	});
	submenu->setChecked(frame->isVisible());
	m_windowmenu->addMenu(submenu);
}

void EditorWindow::handleFrameEvent(EventData* event)
{
	auto evframe = static_cast<EventDataFrame*>(event);
	int menuid = IDMainMenu::Window + event->sourceId;

	auto menu = m_windowmenu->getSubMenuById((IDMainMenu)menuid);
	if (menu)
	{
		menu->setChecked(evframe->evt == EditorFrameEvent::FRAME_OPEN);
	}
}

void EditorWindow::setupMenuBar()
{
	m_menubar = make_share(new EditorMenuBar());
	int size = sizeof(MainMenuConfig) / sizeof(MenuDefineItem);
	for (int i = 0; i < size; i++)
	{
		SharePtr<EditorMenu> menu = CreateMenuByConfig(MainMenuConfig[i]);
		m_menubar->addMenu(menu);
		if (menu->getMenuId() == IDMainMenu::Window)
		{
			m_windowmenu = menu;
		}
	}
}

END_EDITOR_NAMESPACE