#pragma once

#include "editor_common.h"
#include "plugin/IPlugin.h"
#include <functional>
BEGIN_EDITOR_NAMESPACE

#define TRY_GATHER(type, output)	if (auto plugin = getPlugin<DataBind<type>>(); plugin) output = plugin->gather();
#define TRY_PROVIDE(type, output)	if (auto plugin = getPlugin<DataBind<type>>(); plugin) plugin->provide(output);
#define TRY_NOTIFY_CHANGE(type)		if (auto plugin = getPlugin<DataBind<type>>(); plugin) plugin->notifyChange();


template<typename T>
class DataBind : public IPlugin
{
public:

	void registerReference(T& p_reference)
	{
		m_dataPointer = &p_reference;
	}


	void registerProvider(std::function<void(T)> p_provider)
	{
		m_provider = p_provider;
	}


	void registerGatherer(std::function<T(void)> p_gatherer)
	{
		m_gatherer = p_gatherer;
	}


	void provide(T p_data)
	{
		if (m_valueChanged)
		{
			if (m_dataPointer)
				*m_dataPointer = p_data;
			else
				m_provider(p_data);

			m_valueChanged = false;
		}
	}


	void notifyChange()
	{
		m_valueChanged = true;
	}


	T gather()
	{
		return m_dataPointer ? *m_dataPointer : m_gatherer();
	}
	virtual void excute() override {}
private:
	T* m_dataPointer{ nullptr };
	bool m_valueChanged{ false };
	std::function<void(T)> m_provider;
	std::function<T(void)> m_gatherer;
};
END_EDITOR_NAMESPACE