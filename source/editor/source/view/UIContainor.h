#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include <vector>

BEGIN_EDITOR_NAMESPACE

class EditorUIContainor : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorUIContainor)
public:
	EditorUIContainor();
	virtual ~EditorUIContainor();

	template<typename T, typename ... Args>
	T* CreateUI(const Args& ... args)
	{
		T* instance = T::create(args...);
		addChild(instance);
		return instance;
	}

	void addChild(EditorUIBase* chid);
	const std::vector<AutoRef<EditorUIBase>>& getChildrens() { return m_childrens; }
	void clearChildrens();

	void setMarginX(float x) { m_margin.x = x; }
	void setMarginY(float y) { m_margin.y = y; }
	void setMarginTop(float x) { m_margin.z = x; }
	void setMarginBottom(float y) { m_margin.w = y; }
	void setMargin(float x, float y, float top, float btm) { m_margin.x = x; m_margin.y = y; m_margin.z = top; m_margin.w = btm; }
	void setPaddingX(float x) { m_padding.x = x; }
	void setPaddingY(float y) { m_padding.y = y; }
	void setPaddingTop(float x) { m_padding.z = x; }
	void setPaddingBottom(float y) { m_padding.w = y; }
	void setPadding(float x, float y, float top, float btm) { m_padding.x = x; m_padding.y = y; m_padding.z = top; m_padding.w = btm; }
	virtual bool render();
	virtual bool onRender();

	void collectGarbage();
protected:
	std::vector<AutoRef<EditorUIBase>> m_childrens;
	ImVec4 m_margin{8, 4, 0, 0 };
	ImVec4 m_padding{ 0, 0, 0, 0 };
};
END_EDITOR_NAMESPACE