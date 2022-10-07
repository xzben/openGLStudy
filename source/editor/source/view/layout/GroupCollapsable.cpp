#include "GroupCollapsable.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GroupCollapsable)

bool GroupCollapsable::init(const std::string& name)
{
	m_name = name;

	return true;
}

bool GroupCollapsable::onRender()
{
	bool preOpened= m_opened;

	if (ImGui::CollapsingHeader(m_name.c_str(), closable ? &m_opened : nullptr, ImGuiTreeNodeFlags_DefaultOpen))
	{
		Super::onRender();
	}

	if (m_opened != preOpened)
	{
		if(m_opened)
		{
			EventOpen.emit();
		}
		else
		{
			EventClose.emit();
			Destry();
		}
	}

	return true;
}
END_EDITOR_NAMESPACE