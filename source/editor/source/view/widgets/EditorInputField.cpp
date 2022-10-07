#include "EditorInputField.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorInputField)

#define DEFAULT_TEXT_MAX_SIZE 64
#define DEFAULT_INPUTFIELD_SIZE  { 0, 0 }

int EditorInputField::handleInputEventCallback(ImGuiInputTextCallbackData* data)
{
	EditorInputField* input = (EditorInputField*)data->UserData;
	switch (data->EventFlag)
	{
		case ImGuiInputTextFlags_CallbackCompletion:
		{
			input->onInputEnd();
			break;
		}
		case ImGuiInputTextFlags_CallbackEdit:
		{
			if (input->doChangeText(data->Buf))
			{
				input->onInputChange(data->Buf);
			}
			break;
		}
	}

	return 1;
}

EditorInputField::EditorInputField()
{
	setTextMaxCount(DEFAULT_TEXT_MAX_SIZE);
	m_size = DEFAULT_INPUTFIELD_SIZE;
}

bool EditorInputField::onRender()
{
	int flag = ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackCompletion;
	ImGui::InputTextEx(m_guid.c_str(), m_placetips.c_str(), m_text.data(),m_textMaxCount, m_size, flag, EditorInputField::handleInputEventCallback, this);
	
	return true;
}

void EditorInputField::onInputEnd()
{
	EventInputEnd.emit(this);
}

bool EditorInputField::doChangeText(const char* text)
{
	m_text = text;
	return true;
}
void EditorInputField::onInputChange(const char* text)
{
	EventInputChange.emit(this);
}

END_EDITOR_NAMESPACE