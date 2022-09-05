#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorButton : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorButton)
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }

	virtual bool render() override;
private:
	virtual void onClick();
protected:
	std::string m_text{ "" };

};
END_EDITOR_NAMESPACE