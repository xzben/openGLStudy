#pragma once

#include "GfxObject.h"
#include <vector>

BEGIN_OGS_GFX_NAMESPACE

class CommandBuffer;

class Queue : public GfxObject
{
	DECLARE_RUNTIME_CLASS(Queue)
public:
	Queue() :GfxObject(ObjectType::QUEUE) {}
	virtual ~Queue() {};

	void submit(std::vector<AutoRef<CommandBuffer>> cmdBuffs);
protected:
	QueueType m_type{ QueueType::GRAPHICS };
};

END_OGS_GFX_NAMESPACE