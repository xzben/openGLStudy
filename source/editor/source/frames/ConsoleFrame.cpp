#include "ConsoleFrame.h"
#include "view/widgets.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(ConsoleFrame)

const std::vector<std::string> m_logTypes = {
	"all",
	"info",
	"debug",
	"warn",
	"error",
};

void ConsoleFrame::handleInit()
{
	CreateUI<EditorSeparator>();
	auto btnclear = CreateUI<EditorButton>("Clear");
	btnclear->Sameline();
	auto logtype = CreateUI<EditorComBox>(m_logTypes);
	logtype->setWidth(100);
	logtype->Sameline();
	auto filter = CreateUI<EditorTextFilter>("filter");
	filter->setWidth(-10);
	filter->Sameline();
	CreateUI<EditorSeparator>();

	auto content = CreateUI<EditorAreaBox>();
	content->setSize(0, -100);
}

END_EDITOR_NAMESPACE