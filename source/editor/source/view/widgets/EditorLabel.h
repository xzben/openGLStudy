#pragma once

#include "editor_common.h"
#include "view/EditorTitleUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorLabel : public EditorTitleUIBase
{
	DECLARE_RUNTIME_CLASS(EditorLabel)
public:
	const ImVec4& getColor() const { return m_color; }
	void setColor(ImVec4 color) { m_color = color; }
	virtual bool onRender() override;
protected:
	ImVec4 m_color{1, 1, 1, 1};

};
END_EDITOR_NAMESPACE