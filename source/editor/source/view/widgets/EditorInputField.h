#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

class EditorInputField : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorInputField)
public:
	EditorInputField();
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }
	virtual bool onRender() override;
	void setTextMaxCount(int maxCount) { m_textMaxCount = maxCount; m_text.reserve(maxCount); }
	int getTextMaxCount() { return m_textMaxCount; }
protected:
	static int handleInputEventCallback(ImGuiInputTextCallbackData* data);
	void onInputEnd();
	void onInputChange(const char* text);
	bool doChangeText(const char* text);
public:
	OGS::Notify<EditorInputField*> EventInputEnd;
	OGS::Notify<EditorInputField*> EventInputChange;
protected:
	int m_textMaxCount{64};
	std::string m_text{ "" };
	std::string m_placetips{"please input"};
	ImVec4 m_color{ 1, 1, 1, 1 };

};
END_EDITOR_NAMESPACE