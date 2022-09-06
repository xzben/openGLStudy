#include "EditorInputField.h"

BEGIN_EDITOR_NAMESPACE

#define DEFAULT_TEXT_MAX_SIZE 64
#define DEFAULT_INPUTFIELD_SIZE  { 100, 50 }

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
			input->onInputChange();
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

bool EditorInputField::render()
{
	if (!Super::render()) return false;

	int flag = ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackCompletion;
	ImGui::InputTextEx("input", m_placetips.c_str(), m_text.data(),m_textMaxCount, m_size, flag, EditorInputField::handleInputEventCallback, this);
	
	return true;
}

void EditorInputField::onInputEnd()
{

}

void EditorInputField::onInputChange()
{

}
END_EDITOR_NAMESPACE