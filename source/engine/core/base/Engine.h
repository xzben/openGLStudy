#pragma once

#include "common.h"
#include "core/base/Ref.h"
#include "core/tool/Singleton.h"
#include "core/ptr/SharePtr.h"
#include "core/base/System.h"

#include <vector>

BEGIN_OGS_NAMESPACE

class Engine : public Ref, public Singleton<Engine>
{
public:
	Engine();
	virtual ~Engine();

	virtual bool init() override;

protected:
	std::vector<SharePtr<System>> m_systems;
};

END_OGS_NAMESPACE