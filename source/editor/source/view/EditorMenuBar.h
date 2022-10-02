#pragma once

#include "editor_common.h"
#include <vector>
#include <unordered_map>
#include "EditorUIBase.h"
#include "EditorMenu.h"

BEGIN_EDITOR_NAMESPACE

class EditorMenuBar : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorMenuBar)
public:
	EditorMenuBar();
	virtual ~EditorMenuBar();

	void addMenu(EditorMenu* menu);
	void addSubMenu(const std::string& parent, EditorMenu* menu);
	EditorMenu* getMenu(const std::string& name);

	virtual bool onRender() override;
	int getHeight() { return m_heigth; }

private:
	std::unordered_map<std::string, AutoRef<EditorMenu>> m_mapMenus;
	std::vector<AutoRef<EditorMenu>> m_arrMenus;
	int m_heigth{ 18 };
};

END_EDITOR_NAMESPACE