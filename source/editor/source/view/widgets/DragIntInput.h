#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

class DragIntInput : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(DragIntInput)
public:
	virtual bool init(int* data = nullptr);
	virtual bool onRender() override;
private:
	int* m_data{ nullptr };
	int  m_max{ 0 };
	int  m_min{ 0 };
	int  m_speed{ 1 };
};
END_EDITOR_NAMESPACE