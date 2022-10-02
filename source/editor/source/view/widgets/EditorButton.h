#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include <core/base/Notify.h>
BEGIN_EDITOR_NAMESPACE

class EditorButton : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorButton)
public:
	EditorButton() = default;
	virtual bool init(const std::string& text);

	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }

	virtual bool onRender() override;
private:
	virtual void onClick();
protected:
	std::string m_text{ "" };
public:
	OGS::Notify<> ClickedEvent;

};
END_EDITOR_NAMESPACE