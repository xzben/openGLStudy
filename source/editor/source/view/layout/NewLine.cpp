#include "NewLine.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(NewLine)

bool NewLine::onRender()
{
	ImGui::NewLine();

	return true;
}

END_EDITOR_NAMESPACE