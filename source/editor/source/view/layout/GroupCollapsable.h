#pragma once

#include "editor_common.h"
#include "core/base/Notify.h"
#include "view/UIContainor.h"
#include <string>
BEGIN_EDITOR_NAMESPACE

class GroupCollapsable : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(GroupCollapsable)
public:
	virtual bool init(const std::string& name);
	virtual bool onRender() override;
public:
	OGS::Notify<> EventOpen;
	OGS::Notify<> EventClose;
	bool closable{ true };  //ÊÇ·ñÄÜ¹»É¾³ý
protected:
	std::string m_name;
	bool m_opened{ true };

};
END_EDITOR_NAMESPACE