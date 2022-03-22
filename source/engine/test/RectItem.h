#ifndef __RECT_ITEM_2021_09_07_H__
#define __RECT_ITEM_2021_09_07_H__
#include "render/RenderableComponent.h"
#include "common.h"

USING_NAMESPACE;

class RectItem : public RenderableComponent {
private:
	uint m_va;
public:
	RectItem();
	virtual void render();
};
#endif//__RECT_ITEM_2021_09_07_H__