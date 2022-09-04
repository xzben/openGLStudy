#pragma once

#include "common.h"
#include "math/math.h"

BEGIN_OGS_NAMESPACE
class GameView;

class GfxDevice
{
public:
	virtual void swapFrameBuffer() {}
	virtual void clear(Color color) {}

	virtual void setGameView(const SharePtr<GameView>& gameview) { m_gameview = gameview; }
protected:
	SharePtr<GameView> m_gameview;
};

GfxDevice* getCurDvice();
END_OGS_NAMESPACE