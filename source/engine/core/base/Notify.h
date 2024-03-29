#pragma once

#include "common.h"
#include "core/base/Object.h"
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

using ListenerId = uint32;

template<typename ...Args>
class ListenerItem : public Object
{
public:
	ListenerItem(ListenerId id, ItemType t):type(t), m_listenerId(id){}
	virtual void Call(ParmType<Args>... args) = 0;

	ItemType type;
	ListenerId m_listenerId;
};

template<typename T>
class NotifyCalssItemBase
{
public:
	NotifyCalssItemBase(T* owner)
		:m_owner(owner)
	{

	}

	T* m_owner;
};

template<typename T, typename ...Args>
class NotifyClassItem : public NotifyCalssItemBase<T>, public ListenerItem<Args...>
{
public:
	template<typename ...>
	friend class Notify;

	using Super = ListenerItem<Args...>;

	using ListenerFunc = void (T::*)(ParmType<Args>...);
	NotifyClassItem(ListenerId id, T* owner, ListenerFunc func) 
		: Super(id, ItemType::ClassFunc), NotifyCalssItemBase(owner), m_func(func)
	{
	}

	virtual void Call(ParmType<Args>... args) override
	{
		(m_owner->*m_func)(args...);
	}

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
	NotifyFuncItem(ListenerId id, ListenerFunc func) :Super(id, ItemType::NormalFunc), m_func(func){}

	virtual void Call(ParmType<Args>... args)
	{
		m_func(args...);
	}
protected:
	ListenerFunc m_func;
};

template<typename ...Args>
class Notify : public Object
{
public:
	typedef ListenerItem<Args...> ListenerItemType;
	Notify() = default;
	~Notify()
	{
		this->m_items.clear();
	}

	template<typename T>
	ListenerId subscribe(T* obj, void (T::* func)(ParmType<Args>...) )
	{
		m_idcount++;
		subscribe(new NotifyClassItem<T, Args...>(m_idcount, obj, func));

		return m_idcount;
	}

	ListenerId subscribe(std::function<void(ParmType<Args>...)> func)
	{
		m_idcount++;
		subscribe(new NotifyFuncItem<Args...>(m_idcount, func));
		
		return m_idcount;
	}

	ListenerId operator+=(std::function<void(ParmType<Args>...)> func)
	{
		return subscribe(func);
	}

	template<typename T>
	void unsubscribeOwner(T* obj)
	{
		using NotifyItem = NotifyCalssItemBase<T>;
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			NotifyItem* item = dynamic_cast<NotifyItem*>((*it).get());
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
			NotifyClassItem<T, Args...>* item = dynamic_cast<NotifyClassItem<T, Args...>*>((*it).get());
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

	void unsubscribe(ListenerId listenerid)
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			NotifyFuncItem<Args...>* item = dynamic_cast<NotifyFuncItem<Args...>*>(*it);
			if (item != nullptr && item->m_listenerId == listenerid)
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
	void subscribe(ListenerItemType* item)
	{
		m_items.push_back(item);
	}
protected:
	std::vector<AutoRef<ListenerItemType>> m_items;
	ListenerId  m_idcount;
};

END_OGS_NAMESPACE