#pragma once
#include "editor_common.h"
#include "view/EditorTitleUIBase.h"
#include <vector>
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

class EditorComBox : public EditorTitleUIBase
{
	DECLARE_RUNTIME_CLASS(EditorComBox)
public:
	virtual void handleInit() override;
	virtual bool init(const std::vector<std::string>& item);
	void addItem(const std::string& item);
	void setItems(const std::vector<std::string>& items);
	const std::string& getItem(int index);
	int getCurSelect() { m_curIndex; }
	OGS::Notify<int, int> EventChangeSelect; //curselect, preselect
protected:
	virtual bool onRender() override;
private:
	std::vector<std::string> m_items;
	int m_curIndex = 0;
};
END_EDITOR_NAMESPACE