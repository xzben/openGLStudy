#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorLabel : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorLabel)
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }
	const ImVec4& getColor() const { return m_color; }
	void setColor(ImVec4 color) { m_color = color; }
	virtual bool onRender() override;
protected:
	std::string m_text{""};
	ImVec4 m_color{1, 1, 1, 1};

};
END_EDITOR_NAMESPACE