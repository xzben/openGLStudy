#pragma once
#include "editor_common.h"
#include "core/view/GameView.h"
#include "view/UIContainor.h"
BEGIN_EDITOR_NAMESPACE

class HubWindow : public EditorUIContainor
{
public:
	HubWindow(SharePtr<OGS::GameView>& gameview);
public:
	virtual bool init();
	void preRender();
	virtual bool render();
	void postRender();
	virtual void draw();
protected:
	bool initContext();
	bool initUI();
private:
	SharePtr<OGS::GameView> m_gameview;
};

END_EDITOR_NAMESPACE