#pragma once

#include "editor_common.h"
#include <vector>
#include <unordered_map>
#include "EditorUIBase.h"
#include "EditorMenu.h"

BEGIN_EDITOR_NAMESPACE

class EditorMenuBar : public EditorUIBase
{
public:
	typedef ThisType Super;
	typedef EditorMenuBar ThisType;

	EditorMenuBar();
	virtual ~EditorMenuBar();

	void addMenu(SharePtr<EditorMenu> menu);
	void addSubMenu(const std::string& parent, SharePtr<EditorMenu> menu);
	EditorMenu* getMenu(const std::string& name);

	virtual bool render() override;
	int getHeight() { return m_heigth; }

private:
	std::unordered_map<std::string, SharePtr<EditorMenu>> m_mapMenus;
	std::vector<SharePtr<EditorMenu>> m_arrMenus;
	int m_heigth{ 18 };
};

END_EDITOR_NAMESPACE