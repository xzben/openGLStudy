#include "DragFloatInput.h"

BEGIN_EDITOR_NAMESPACE
IMPLEMENT_RUNTIME_CLASS(DragFloatInput)
bool DragFloatInput::init(float* data /*= nullptr*/)
{
	if (data == nullptr)
	{
		m_data = new float(0.0);
	}
	else
	{
		m_data = data;
	}

	return true;
}

bool DragFloatInput::onRender()
{
	ImGui::DragFloat(m_guid.c_str(), m_data, m_speed, m_min, m_min, "%.3f");

	return true;
}

END_EDITOR_NAMESPACE