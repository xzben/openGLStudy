#include "EditorMenu.h"
#include "imgui.h"
#include "event/EditorEventMgr.h"
#include "EditorApp.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorMenu)

bool EditorMenu::onRender()
{
	if (renderAsContainor()) return true;
	if (renderAsWidget()) return true;

	renderAsItem();

	return true;
}

bool EditorMenu::renderAsContainor()
{
	if (m_menus.size() <= 0) return false;
	if (ImGui::BeginMenu(m_name.c_str(), m_enable))
	{
		for (auto menu : m_menus)
		{
			menu->render();
		}
		ImGui::EndMenu();
	}

	return true;
}

bool EditorMenu::renderAsWidget()
{
	if (m_widget == nullptr) return false;

	m_widget->render();

	return true;
}

void EditorMenu::onClick(bool ischeck)
{
	if (m_menuId > 0)
	{
		EditorMenuEvent event = EditorMenuEvent::MENU_CLICK;
		if (m_checkable)
		{
			event = ischeck ? EditorMenuEvent::MENU_CHECKED : EditorMenuEvent::MENU_UNCHECKED;
		}

		EventData* pevent = new EventDataMenu(this->m_menuId, event);
		EditorEventMgr::GetInstance()->emitEvent(EditorEvent::MENU, pevent);
		SAFE_DELTE(pevent);
	}
	if (m_clickcall)
	{
		m_clickcall(ischeck);
	}
}

EditorMenu* EditorMenu::getSubMenuById(IDMainMenu menuid)
{
	for (auto it : m_menus)
	{
		if (it->getMenuId() == menuid)
		{
			return it.get();
		}
	}

	return nullptr;
}

bool EditorMenu::renderAsItem()
{
	bool isCheck = m_checkable ? m_checked : false;
	if (ImGui::MenuItem(m_name.c_str(), m_shortcuts.c_str(), isCheck, m_enable))
	{
		if (m_checkable) m_checked = !m_checked;
		onClick(!isCheck);
	}
	return true;
}

END_EDITOR_NAMESPACE