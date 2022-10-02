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

	virtual bool onRender();
protected:
	std::vector<AutoRef<EditorUIBase>> m_childrens;
};
END_EDITOR_NAMESPACE