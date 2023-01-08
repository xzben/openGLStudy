#pragma once

#include "common.h"
#include "core/base/Component.h"
#include "core/base/Notify.h"

BEGIN_OGS_NAMESPACE

class Button : public Component
{
public:
	Button();

public:
	Notify<> ClickEvent;
};

END_OGS_NAMESPACE