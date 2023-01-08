#include "InspectorUIRenderRegister.h"
#include "InspectorUIMgr.h"
#include "view/UIContainor.h"
#include "view/widgets.h"
#include "core/math/math.h"
#include "inspector_define.h"
BEGIN_EDITOR_NAMESPACE

void registerCommonInspectorUI(InspectorUIMgr* mgr)
{
	mgr->registerUIRender<Vector3>([](const std::string& name, void* obj)->EditorUIBase* {
		OGS::Vector3* data = (OGS::Vector3*)obj;
		
		auto* ui = LayoutColumns<2>::create();
		ui->widths[0] = INSPECTOR_NAME_WIDTH;
		ui->CreateUI<EditorLabel>(name);
		ui->CreateUI<EditorUIRenderFunc>([data](EditorUIRenderFunc* self) {
			ImGui::DragFloat3(self->getGuiD().c_str(), data->value, 0.001, 0, 0, "%.3f");
		});
		return ui;
	});

	mgr->registerUIRender<float>([](const std::string& name, void* obj)->EditorUIBase* {
		float* data = (float*)obj;

		auto* ui = LayoutColumns<2>::create();
		ui->widths[0] = INSPECTOR_NAME_WIDTH;
		ui->CreateUI<EditorLabel>(name);
		ui->CreateUI<EditorUIRenderFunc>([data](EditorUIRenderFunc* self) {
			ImGui::DragFloat(self->getGuiD().c_str(), data, 0.001, 0, 0, "%.3f");
			});
		return ui;
	});

	mgr->registerUIRender<int>([](const std::string& name, void* obj)->EditorUIBase* {
		int* data = (int*)obj;

		auto* ui = LayoutColumns<2>::create();
		ui->widths[0] = INSPECTOR_NAME_WIDTH;
		ui->CreateUI<EditorLabel>(name);
		ui->CreateUI<EditorUIRenderFunc>([data](EditorUIRenderFunc* self) {
			ImGui::DragInt(self->getGuiD().c_str(), data, 1, 0, 0, "%d");
			});
		return ui;
	});

	mgr->registerUIRender<std::string>([](const std::string& name, void* obj)->EditorUIBase* {
		std::string* data = (std::string*)obj;

		auto* ui = LayoutColumns<2>::create();
		ui->widths[0] = INSPECTOR_NAME_WIDTH;
		ui->CreateUI<EditorLabel>(name);
		auto input = ui->CreateUI<EditorInputField>();
		
		input->EventInputChange += [data](EditorInputField* self) {
			*data = self->getText();
		};

		return ui;
	});

	mgr->registerUIRender<Color>([](const std::string& name, void* obj)->EditorUIBase* {
		Color* data = (Color*)obj;

		auto* ui = LayoutColumns<2>::create();
		ui->widths[0] = INSPECTOR_NAME_WIDTH;
		ui->CreateUI<EditorLabel>(name);
		ui->CreateUI<EditorUIRenderFunc>([data](EditorUIRenderFunc* self) {
			ImGui::ColorEdit4(self->getGuiD().c_str(), data->value, ImGuiColorEditFlags_Float);
		});
		return ui;
	});
}

END_EDITOR_NAMESPACE