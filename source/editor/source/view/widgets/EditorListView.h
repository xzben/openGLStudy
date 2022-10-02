#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include <vector>
BEGIN_EDITOR_NAMESPACE

class EditorListView : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorListView)
public:
	virtual bool onRender() override;

	void addItem(AutoRef<EditorUIBase> item) { m_items.push_back(item); }
private:
	std::vector<AutoRef<EditorUIBase>> m_items;
};
END_EDITOR_NAMESPACE