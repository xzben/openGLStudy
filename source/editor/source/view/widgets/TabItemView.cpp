#include "TabItemView.h"

BEGIN_EDITOR_NAMESPACE
IMPLEMENT_RUNTIME_CLASS(TabItemView)

bool TabItemView::init(const std::string& title)
{
	m_title = title;

	return true;
}

bool TabItemView::onRender()
{
	if (ImGui::BeginTabItem(m_title.c_str()))
	{
		Super::onRender();
		ImGui::EndTabItem();
	}

	return true;
}

END_EDITOR_NAMESPACE