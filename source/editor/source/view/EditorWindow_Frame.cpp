#include "EditorWindow.h"
#include "DefineId.h"
#include "EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

static SharePtr<EditorFrame> createNodeTreeFrame(const char* name)
{
	return make_share(new EditorFrame(name));
}

static SharePtr<EditorFrame> createAssetsFrame(const char* name)
{
	return make_share(new EditorFrame(name));
}


static SharePtr<EditorFrame> createGameViewFrame(const char* name)
{
	return make_share(new EditorFrame(name));
}


static SharePtr<EditorFrame> createConsoleFrame(const char* name)
{
	return make_share(new EditorFrame(name));
}

static SharePtr<EditorFrame> createAttrFrame(const char* name)
{
	return make_share(new EditorFrame(name));
}

using EditorFrameCreator = std::function<SharePtr<EditorFrame>(const char*)>;

struct FrameConfig
{
	IDMainFrame id;
	MainDockSpace spaceid;
	const char* name;
	EditorFrameCreator creator;
};

static FrameConfig DefaultFrames[] = {
	{ IDMainFrame::NODE_TREE,	MainDockSpace::LEFT_TOP,		"node tree",	&createNodeTreeFrame},
	{ IDMainFrame::ASSET_VIEW,	MainDockSpace::LEFT_BOTTOM,		"assets",		&createAssetsFrame},
	{ IDMainFrame::GAME_VIEW,	MainDockSpace::CENTER_TOP,		"game view",	&createGameViewFrame},
	{ IDMainFrame::CONSOLE_VIEW,MainDockSpace::CENTER_BOTTOM,	"console",		&createConsoleFrame},
	{ IDMainFrame::ATTR_VIEW,	MainDockSpace::RIGHT,			"attr view",	&createAttrFrame},
	//{ IDMainFrame::ATTR_VIEW_2,	MainDockSpace::RIGHT,			"attr view2",	&createAttrFrame},
};

SharePtr<EditorFrame> createFrameByConfig(const FrameConfig& config )
{
	SharePtr<EditorFrame> frame = config.creator(config.name);
	frame->setDockspaceId(config.spaceid);
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
		addFrame(frame);
	}
}

void EditorWindow::addFrame(SharePtr<EditorFrame>& frame)
{
	m_frames.push_back(frame);
	createFrameWindowSubMenu(m_frames.size(), frame);
}

END_EDITOR_NAMESPACE