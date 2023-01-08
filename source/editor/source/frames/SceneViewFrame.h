#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

namespace OGS {
	class Camera;
	class RenderWindow;
}


BEGIN_EDITOR_NAMESPACE



class SceneViewFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(SceneViewFrame)
public:
	SceneViewFrame(){}
protected:
	virtual void renderImp() override;
	void handleInit() override;
	void handleFrameSizeChange() override;
private:
	AutoRef<OGS::Camera> m_editorCamera;
	AutoRef<OGS::RenderWindow> m_renderWindow;

};
END_EDITOR_NAMESPACE