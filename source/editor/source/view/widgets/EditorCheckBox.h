#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorCheckBox : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorCheckBox)
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }
	
	virtual bool render() override;
	bool isChecked() { return m_isChecked; }
	void setChecked(bool checked) { m_isChecked = checked; }
protected:
	std::string m_text{ "" };
	bool m_isChecked;
};
END_EDITOR_NAMESPACE