#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "core/base/Notify.h"

BEGIN_OGS_NAMESPACE

class ButtonComponent : public Component
{
public:
	typedef Notify<> NotifyClick;
	ButtonComponent();

public:
	NotifyClick m_notifyClick;
};

END_OGS_NAMESPACE