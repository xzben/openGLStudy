#pragma once

#include "editor_common.h"
#include "IPlugin.h"
#include <vector>

BEGIN_EDITOR_NAMESPACE


class Pluginable
{
public:
	~Pluginable()
	{
		removeAllPlugin();
	}

	template<typename T, typename ...Args>
	T& addPlugin(Args&&... args)
	{
		static_assert(std::is_base_of<IPlugin, T>::value, "T should derive from IPlugin");
		T* plugin = new T(std::forward<Args>(args)...);
		addPlugin(plugin);

		return *plugin;
	}

	template<typename T>
	T* getPlugin()
	{
		static_assert(std::is_base_of<IPlugin, T>::value, "T should derive from IPlugin");

		for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
		{
			T* result = dynamic_cast<T*>(*it);
			if (result)
				return result;
		}

		return nullptr;
	}

	void addPlugin(IPlugin* plugin)
	{
		m_plugins.push_back(plugin);
	}

	void removeAllPlugin()
	{
		for (auto& plugin : m_plugins)
		{
			delete plugin;
		}
		m_plugins.clear();
	}
protected:
	void executePlugins()
	{
		for (auto& plugin : m_plugins)
		{
			plugin->excute();
		}
	}
protected:
	std::vector<IPlugin*> m_plugins;
};
END_EDITOR_NAMESPACE