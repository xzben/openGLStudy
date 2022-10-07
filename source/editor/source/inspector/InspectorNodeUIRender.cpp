#include "InspectorUIRenderRegister.h"
#include "InspectorUIMgr.h"
#include "core/base/Component.h"
#include "view/widgets.h"
#include "inspector/inspector_define.h"
#include "core/base/Node.h"

BEGIN_EDITOR_NAMESPACE

void registerNodeUIRender(InspectorUIMgr* mgr)
{
	mgr->registerUIRender<OGS::Component>([mgr](const std::string& name, void* data)->EditorUIBase* {
		OGS::Component* com = (OGS::Component*)data;
		OGS::Runtime* runtime = com->GetRuntime();
		OGS::ReflexClassBase* rfcls = com->GetReflex();
		GroupCollapsable* ui = GroupCollapsable::create(runtime->getName());
		
		rfcls->foreachFields([ui, mgr, com](OGS::ReflexClassFieldBase* field)->void{
			void* fdata = field->getFieldData(com);
			ui->addChild(mgr->getUIObject(field->getRawTypeName(),field->GetRawName(), fdata));
		});

		return ui;
	});

	mgr->registerUIRender<OGS::Node>([mgr](const std::string& name, void* data)->EditorUIBase* {
		OGS::Node* node = (OGS::Node*)data;

		auto ui = EditorAreaBox::create();
		auto cbxEnable = ui->CreateUI<EditorCheckBox>();
		cbxEnable->Sameline();
		cbxEnable->setChecked(node->isActive());
		cbxEnable->EventCheck += [node](bool checked) {
			node->setActive(checked);
		};
		auto inputname = ui->CreateUI<EditorInputField>();
		inputname->setText(node->getName());
		inputname->EventInputChange += [node](EditorInputField* input) {
			node->setName(input->getText());
		};

		auto comps = node->getAllComponents();
		for (auto it = comps.begin(); it != comps.end(); it++)
		{
			Component* com = *it;
			ui->addChild(mgr->getUIObject<OGS::Component>(com));
		}

		return ui;
	});
}
END_EDITOR_NAMESPACE