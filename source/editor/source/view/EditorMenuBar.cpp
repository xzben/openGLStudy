#include "EditorMenuBar.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "event/EditorEventMgr.h"
#include "core/view/GameView.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorMenuBar)

EditorMenuBar::EditorMenuBar()
{

}

EditorMenuBar::~EditorMenuBar()
{
	m_arrMenus.clear();
	m_mapMenus.clear();
}

bool EditorMenuBar::onRender()
{
	if (ImGui::BeginMainMenuBar())
	{
		for (auto menu : m_arrMenus)
		{
			menu->render();
		}
		ImGui::EndMainMenuBar();
	}

	return true;
}

void EditorMenuBar::addMenu(EditorMenu* pmenu)
{
	m_arrMenus.push_back(pmenu);
	m_mapMenus.insert(std::make_pair(pmenu->getName(), pmenu));
}

void EditorMenuBar::addSubMenu(const std::string& parent, EditorMenu* pmenu)
{
	if (pmenu == nullptr) return;

	auto it = m_mapMenus.find(parent);
	if (it == m_mapMenus.end())
	{
		CCLOG_ERROR("can't find the menu by name[%s]", parent.c_str());
		return;
	}

	it->second->addMenu(pmenu);
	
}

EditorMenu* EditorMenuBar::getMenu(const std::string& name)
{
	auto it = m_mapMenus.find(name);
	if (it == m_mapMenus.end())
	{
		return nullptr;
	}

	return it->second.get();
}

END_EDITOR_NAMESPACE