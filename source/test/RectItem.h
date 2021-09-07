#ifndef __RECT_ITEM_2021_09_07_H__
#define __RECT_ITEM_2021_09_07_H__
#include "base/RenderNode.h"
#include "common.h"

class RectItem : public RenderNode {
private:
	uint m_va;
public:
	RectItem();
	virtual void render();
};
#endif//__RECT_ITEM_2021_09_07_H__