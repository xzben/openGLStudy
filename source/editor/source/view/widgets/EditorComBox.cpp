#include "EditorComBox.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorComBox)

bool EditorComBox::init(const std::vector<std::string>& item)
{
	setItems(item);
	return true;
}

void EditorComBox::handleInit()
{

}

void EditorComBox::addItem(const std::string& item)
{
	m_items.push_back(item);
}

void EditorComBox::setItems(const std::vector<std::string>& items)
{
	m_items = items;
}

const std::string& EditorComBox::getItem(int index)
{
	ASSERT(index < m_items.size(), "index out of range");

	return m_items[index];
}

bool EditorComBox::onRender()
{
	int count = m_items.size();
	int preIndex = m_curIndex;

	ImGui::Combo(m_guid.c_str(), &m_curIndex, [](void* data, int idx, const char** out_text)->bool {
		EditorComBox* self = (EditorComBox*)data;
		const std::string& text = self->getItem(idx);
		*out_text = text.c_str();

		return true;
	}, this, count, count);

	if (preIndex != m_curIndex)
	{
		EventChangeSelect.emit(m_curIndex, preIndex);
	}

	return true;
}

END_EDITOR_NAMESPACE