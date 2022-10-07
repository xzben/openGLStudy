#include "UIContainor.h"
#include "EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorUIContainor)

EditorUIContainor::EditorUIContainor()
{

}

EditorUIContainor::~EditorUIContainor()
{

}

void EditorUIContainor::collectGarbage()
{
	for (auto it = m_childrens.begin(); it != m_childrens.end();)
	{
		if ((*it)->isDirtyRemove())
		{
			it = m_childrens.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool EditorUIContainor::render()
{
	bool ok = Super::render();
	collectGarbage();

	return ok;
}

bool EditorUIContainor::onRender()
{
	for (auto ui : m_childrens)
	{
		ui->render();
	}
	
	return true;
}

void EditorUIContainor::addChild(EditorUIBase* chid)
{
	chid->setParent(this);
	m_childrens.push_back(chid);
}

void EditorUIContainor::clearChildrens()
{
	for (auto chid : m_childrens)
	{
		chid->setParent(nullptr);
	}
	m_childrens.clear();
}
END_EDITOR_NAMESPACE