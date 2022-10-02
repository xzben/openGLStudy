#pragma once

#include "common.h"
#include "math/math.h"
#include "core/base/Object.h"

BEGIN_OGS_NAMESPACE
class GameView;

class GfxDevice : public Object
{
	DECLARE_RUNTIME_CLASS(GfxDevice)
public:
	virtual bool init() { return true; }
	virtual void processEvent(){}
	virtual void swapFrameBuffer() {}
	virtual void clear(Color color) {}
	virtual void GetScreenSize(int& width, int& height) { width = 0; height = 0; };
	virtual void setGameView(GameView* gameview);
protected:
	AutoRef<GameView> m_gameview;
};


GfxDevice* createCurDevice();
END_OGS_NAMESPACE