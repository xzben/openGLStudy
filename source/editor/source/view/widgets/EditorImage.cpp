#include "EditorImage.h"

BEGIN_EDITOR_NAMESPACE

bool EditorImage::render()
{
	if (!Super::render())
		return false;

	//ImGui::Image(,m_size)
	
	return true;
}

END_EDITOR_NAMESPACE