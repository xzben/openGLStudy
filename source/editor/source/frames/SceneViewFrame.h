#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

namespace OGS {
	class Camera;
	namespace Gfx
	{
		class FrameBuffer;
		class Texture;
	}
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
	AutoRef<OGS::Gfx::FrameBuffer> m_framebuffer;
	AutoRef<OGS::Gfx::Texture> m_colorTex;
};
END_EDITOR_NAMESPACE