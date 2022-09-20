#include "UIContainor.h"
#include "EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

EditorUIContainor::EditorUIContainor()
{

}

EditorUIContainor::~EditorUIContainor()
{

}

bool EditorUIContainor::onRender()
{
	for (auto ui : m_childrens)
	{
		ui->render();
	}
	
	return true;
}

END_EDITOR_NAMESPACE