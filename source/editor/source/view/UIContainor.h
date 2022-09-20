#pragma once

#include "editor_common.h"
#include <vector>
BEGIN_EDITOR_NAMESPACE

class EditorUIBase;

class EditorUIContainor
{
public:
	EditorUIContainor();
	virtual ~EditorUIContainor();

	template<typename T, typename ... Args>
	SharePtr<T> CreateUI(Args&& ... args)
	{
		auto instance = makeShare(new T(args...));
		m_childrens.push_back(instance);
		return instance;
	}

	virtual bool onRender();
protected:
	std::vector<SharePtr<EditorUIBase>> m_childrens;
};
END_EDITOR_NAMESPACE