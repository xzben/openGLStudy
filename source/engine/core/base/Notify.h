#pragma once

#include "common.h"
#include <vector>
#include <functional>

BEGIN_OGS_NAMESPACE

enum class ItemType
{
	NormalFunc,
	ClassFunc
};

template<typename Arg>
using ParmType = std::conditional_t<std::is_pointer_v<Arg>, Arg, const Arg&>;

template<typename ...Args>
class ListenerItem
{
public:
	ListenerItem(ItemType t):type(t){}
	virtual void Call(ParmType<Args>... args) = 0;
	virtual bool operator==(const ListenerItem<Args...>& rhs)
	{
		return type == rhs.type;
	}
	ItemType type;
};

template<typename T, typename ...Args>
class NotifyClassItem : public ListenerItem<Args...>
{
public:
	template<typename ...>
	friend class Notify;

	using Super = ListenerItem<Args...>;

	using ListenerFunc = void (T::*)(ParmType<Args>...);
	NotifyClassItem(T* owner, ListenerFunc func) : Super(ItemType::ClassFunc), m_owner(owner), m_func(func) {}

	virtual void Call(ParmType<Args>... args) override
	{
		(m_owner->*m_func)(args...);
	}

	virtual bool operator==(const NotifyClassItem<T, Args...>& rhs)
	{
		return m_owner == rhs.m_owner && m_func == rhs.m_func;
	}
protected:
	T* m_owner;
	ListenerFunc m_func;
};

template<typename ...Args>
class NotifyFuncItem : public ListenerItem<Args...>
{
public:
	template<typename ...>
	friend class Notify;
	using Super = ListenerItem<Args...>;
	typedef std::function<void(ParmType<Args>...)> ListenerFunc;
	NotifyFuncItem(ListenerFunc func) :Super(ItemType::NormalFunc), m_func(func){}

	virtual void Call(ParmType<Args>... args)
	{
		m_func(args...);
	}

	virtual bool operator==(const NotifyFuncItem<Args...>& rhs) override
	{
		return m_func == rhs.m_func;
	}
protected:
	ListenerFunc m_func;
};

template<typename ...Args>
class Notify
{
public:
	typedef ListenerItem<Args...> ListenerItemType;
	Notify() = default;
	~Notify()
	{
		this->m_items.clear();
	}

	template<typename T>
	void subscribe(T* obj, void (T::* func)(ParmType<Args>...) )
	{
		subscribe(new NotifyClassItem<T, Args...>(obj, func));
	}

	void subscribe(std::function<void(ParmType<Args>...)> func)
	{
		subscribe(new NotifyFuncItem<Args...>(func));
	}

	void subscribe(ListenerItemType* item)
	{
		m_items.push_back(item);
	}

	template<typename T>
	void unsubscribeOwner(T* obj)
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			NotifyClassItem<T, Args...>* item = dynamic_cast<NotifyClassItem<T, Args...>>(it);
			if (item != nullptr && item->m_owner == obj)
			{
				it = m_items.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	template<typename T>
	void unsubscribe(T* obj, void (T::* func)(ParmType<Args>...) )
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			NotifyClassItem<T, Args...>* item = dynamic_cast<NotifyClassItem<T, Args...>*>(*it);
			if (item != nullptr && item->m_owner == obj && item->m_func == func)
			{
				it = m_items.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void unsubscribe(std::function<void(ParmType<Args>...)> func)
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			NotifyFuncItem<Args...>* item = dynamic_cast<NotifyFuncItem<Args...>*>(*it);
			if (item != nullptr && item->m_func == func)
			{
				it = m_items.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void unsubscribe(ListenerItemType* item)
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			if (item->type == (*it)->type &&  (*it) == item)
			{
				it = m_items.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void emit(ParmType<Args>... args)
	{
		for (auto item : this->m_items)
		{
			item->Call(args...);
		}
	}
protected:
	std::vector<ListenerItemType*> m_items;
};

END_OGS_NAMESPACE