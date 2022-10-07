#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include "plugin/DataBind.h"
BEGIN_EDITOR_NAMESPACE

template<typename T>
class DataBindUIBase : public EditorUIBase
{
public:
	DataBindUIBase(T& dataholder) : m_data(dataholder) {};

	virtual bool render() override
	{
		if (m_isVisible)
		{
			TRY_GATHER(T, m_data);
			EditorUIBase::render();
			TRY_PROVIDE(T, m_data);
		}
	}

	void notifyChange()
	{
		TRY_NOTIFY_CHANGE(T);
	}
private:
	T& m_data;
};
END_EDITOR_NAMESPACE