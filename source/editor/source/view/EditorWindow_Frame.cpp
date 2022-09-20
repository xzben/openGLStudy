#include "EditorWindow.h"
#include "DefineId.h"
#include "EditorFrame.h"
#include "frames/AssetsFrame.h"
#include "frames/ConsoleFrame.h"
#include "frames/GameViewFrame.h"
#include "frames/SceneViewFrame.h"
#include "frames/InspectorFrame.h"
#include "frames/NodeTreeFrame.h"

BEGIN_EDITOR_NAMESPACE

static FrameConfig DefaultFrames[] = {
	{ IDMainFrame::NODE_TREE,	MainDockSpace::LEFT_TOP,		"NodeTree",	&NodeTreeFrame::create},
	{ IDMainFrame::ASSET_VIEW,	MainDockSpace::LEFT_BOTTOM,		"Assets",		&AssetsFrame::create},
	{ IDMainFrame::SCENE_VIEW,	MainDockSpace::CENTER_TOP,		"SceneView",	&SceneViewFrame::create},
	{ IDMainFrame::GAME_VIEW,	MainDockSpace::CENTER_TOP,		"GameView",	&GameViewFrame::create},
	{ IDMainFrame::CONSOLE_VIEW,MainDockSpace::CENTER_BOTTOM,	"Console",		&ConsoleFrame::create},
	{ IDMainFrame::INSPECTOR_VIEW,	MainDockSpace::RIGHT,		"Inspector",	&InspectorFrame::create},
	//{ IDMainFrame::ATTR_VIEW_2,	MainDockSpace::RIGHT,			"attr view2",	&createAttrFrame},
};

SharePtr<EditorFrame> createFrameByConfig(const FrameConfig& config )
{
	SharePtr<EditorFrame> frame = config.creator();
	frame->setTitle(config.name);
	frame->setMainFrameId(config.id);
	return frame;
}

void EditorWindow::setupFrames()
{
	int size = sizeof(DefaultFrames) / sizeof(FrameConfig);
	for (int i = 0; i < size; i++)
	{
		FrameConfig& config = DefaultFrames[i];
		SharePtr<EditorFrame> frame = createFrameByConfig(config);
		addFrame(frame, config);
	}
}

void EditorWindow::addFrame(SharePtr<EditorFrame>& frame, const FrameConfig& config)
{
	m_frames.push_back({ frame, config });
	createFrameWindowSubMenu(m_frames.size(), frame);
}

END_EDITOR_NAMESPACE