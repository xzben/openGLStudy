#pragma once
#include "editor_common.h"
#include "view/EditorTitleUIBase.h"
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

class EditorTextFilter : public EditorTitleUIBase
{
	DECLARE_RUNTIME_CLASS(EditorTextFilter)
public:
	bool passFilter(const char* text, const char* text_end = nullptr);
	void clear();
	bool isActive();
protected:
	virtual bool onRender();

public:
	OGS::Notify<>			 EventFilterChange;
private:
	ImGuiTextFilter       m_filter;
	int					  m_width{100};
};
END_EDITOR_NAMESPACE