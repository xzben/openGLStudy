#include "InspectorFrame.h"
#include "EditorApp.h"
#include "project/GameProject.h"
#include "core/assets/items/Asset.h"
#include "core/base/Node.h"
#include "inspector/InspectorUIMgr.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(InspectorFrame)

void InspectorFrame::handleInit()
{
	auto project = EditorApp::getInstance()->GetProject();
	project->EventActiveAssetChange += [this](OGS::Asset* asset) {
		this->updateView(asset);
	};

	project->EventActiveNodeChange += [this](OGS::Node* node) {
		this->updateView(node);
	};
}

void InspectorFrame::updateView(OGS::Object* obj)
{
	if (m_showObject == obj) return;
	m_showObject = obj;
	clearChildrens();

	EditorUIBase* ui = nullptr;
	if (obj)
	{
		if (obj->ToCast<OGS::Asset>())
		{
			ui = InspectorUIMgr::getInstance()->getUIObject(obj->ToCast<OGS::Asset>());
		}
		else if (obj->ToCast<OGS::Node>())
		{
			ui = InspectorUIMgr::getInstance()->getUIObject<OGS::Node>(obj->ToCast<OGS::Node>());
		}
	}

	if (ui)
	{
		this->addChild(ui);
	}
}

END_EDITOR_NAMESPACE