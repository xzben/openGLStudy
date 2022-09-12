#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "core/ptr/SharePtr.h"
#include "core/base/System.h"

#include <vector>

BEGIN_OGS_NAMESPACE

class GfxDevice;
class GameView;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	virtual bool init();
	virtual void update(float dt);
protected:
	std::vector<SharePtr<System>> m_systems;
};

END_OGS_NAMESPACE