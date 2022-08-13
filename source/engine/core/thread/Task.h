#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE


class Task
{
public:
	Task() {};
	virtual ~Task() {};
	virtual void doJob() = 0;
};

END_OGS_NAMESPACE