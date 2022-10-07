#include "EditorTitleUIBase.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorTitleUIBase)

bool EditorTitleUIBase::init(const std::string& title)
{
	m_title = title;

	return true;
}

END_EDITOR_NAMESPACE