#include "EditorTextFilter.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorTextFilter)

bool EditorTextFilter::onRender()
{
	if (m_filter.Draw(m_guid.c_str(), m_size.x))
	{
		EventFilterChange.emit();
	}

	return true;
}

bool EditorTextFilter::passFilter(const char* text, const char* text_end /*= nullptr*/)
{
	return m_filter.PassFilter(text, text_end);
}

void EditorTextFilter::clear()
{
	m_filter.Clear();
}

bool EditorTextFilter::isActive()
{
	return m_filter.IsActive();
}
END_EDITOR_NAMESPACE