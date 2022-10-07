#include "TabView.h"
#include "TabItemView.h"
BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(TabView)

bool TabView::onRender()
{
	if (ImGui::BeginTabBar(m_guid.c_str()))
	{
		Super::onRender();
		ImGui::EndTabBar();
	}
	return true;
}

TabItemView* TabView::addTabItem(const std::string& name)
{
	TabItemView* tab = TabItemView::create(name);
	addChild(tab);
	return tab;
}


END_EDITOR_NAMESPACE