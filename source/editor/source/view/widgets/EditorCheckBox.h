#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

class EditorCheckBox : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorCheckBox)
public:	
	virtual bool onRender() override;
	bool isChecked() { return m_isChecked; }
	void setChecked(bool checked) { m_isChecked = checked; }
	OGS::Notify<bool> EventCheck;
protected:
	bool m_isChecked;
};
END_EDITOR_NAMESPACE