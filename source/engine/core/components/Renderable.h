#pragma once


#include "common.h"
#include "core/base/Component.h"

BEGIN_OGS_NAMESPACE

class Renderable : public Component
{
public:
	Renderable();
	virtual ~Renderable();

protected:
	virtual void onStart() override;
	virtual void onStop() override;
};

END_OGS_NAMESPACE