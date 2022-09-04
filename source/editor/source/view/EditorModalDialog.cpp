#include "EditorModalDialog.h"

BEGIN_EDITOR_NAMESPACE

EditorModalDialog::EditorModalDialog()
{

}

EditorModalDialog::~EditorModalDialog()
{

}

bool EditorModalDialog::render()
{
	if (!Super::render()) return false;

	return true;
}

END_EDITOR_NAMESPACE