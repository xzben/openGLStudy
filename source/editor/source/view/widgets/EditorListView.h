#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include <vector>
BEGIN_EDITOR_NAMESPACE

class EditorListView : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorListView)
public:
	virtual bool render() override;

	void addItem(SharePtr<EditorUIBase> item) { m_items.push_back(item); }
private:
	std::vector<SharePtr<EditorUIBase>> m_items;
};
END_EDITOR_NAMESPACE