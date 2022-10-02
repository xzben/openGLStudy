#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"
#include <vector>
#include <string>
#include <functional>

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class EditorMenu : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorMenu)
public:
	using MenuClickCallback = std::function<void(bool)>;
	EditorMenu() = default;
	EditorMenu(IDMainMenu id, const std::string& name, const std::string& shortcuts) :m_name(name), m_menuId(id), m_shortcuts(shortcuts) {}
	virtual ~EditorMenu() = default;

	void setShortCuts(const std::string& shortcuts) { m_shortcuts = shortcuts; }
	void setOrder(int order) { m_order = order; }
	void setParent(EditorMenu* parent) { m_parent = parent; }
	int getOrder() const { return m_order; }
	const std::string& getName() const { return m_name; }
	void addMenu(EditorMenu* menu) { m_menus.push_back(menu); menu->setParent(this); }
	EditorMenu* getSubMenuById(IDMainMenu menuid);
	void setItemCheckable(bool checkable) { m_checkable = checkable; }
	void setClickCallback(MenuClickCallback callback) { m_clickcall = callback; }
	void setChecked(bool check) { m_checked = check; }
	IDMainMenu getMenuId() { return m_menuId; }
	virtual bool onRender() override;
protected:
	virtual void onClick(bool ischeck);
private:
	bool renderAsContainor();
	bool renderAsItem();
	bool renderAsWidget();
protected:
	MenuClickCallback m_clickcall = nullptr;
	std::string m_name{""};
	IDMainMenu m_menuId{0};
	int m_order{0};
	EditorMenu* m_parent;
	std::string m_shortcuts{""};
	AutoRef<EditorUIBase> m_widget;
	std::vector<AutoRef<EditorMenu>> m_menus;
	bool m_checked{false};
	bool m_checkable{ false };
};

END_EDITOR_NAMESPACE