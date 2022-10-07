#include "DragIntInput.h"

BEGIN_EDITOR_NAMESPACE
IMPLEMENT_RUNTIME_CLASS(DragIntInput)
bool DragIntInput::init(int* data /*= nullptr*/)
{
	if (data == nullptr)
	{
		m_data = new int(0.0);
	}
	else
	{
		m_data = data;
	}
	return true;
}

bool DragIntInput::onRender()
{
	ImGui::DragInt(m_guid.c_str(), m_data, m_speed, m_min, m_min, "%d");
	return true;
}

END_EDITOR_NAMESPACE