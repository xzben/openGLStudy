#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

class DragFloatInput : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(DragFloatInput)
public:
	virtual bool init(float* data = nullptr);
	virtual bool onRender() override;
private:
	float* m_data{ nullptr };
	float  m_max{0};
	float  m_min{0};
	float  m_speed{0.1};
};
END_EDITOR_NAMESPACE