#pragma once

#include "common.h"
#include "Ref.h"
#include <vector>
#include <functional>

BEGIN_OGS_NAMESPACE

template<typename ...Args>
class ListenerItem
{
public:
	virtual void Call(Args... args) = 0;
	virtual bool operator==(const ListenerItem<Args...>& rhs) = 0;
};

template<typename T, typename ...Args>
class NotifyClassItem : public ListenerItem<Args...>
{
public:
	typedef void (T::* ListenerFunc)(Args...);
	NotifyClassItem(T* owner, ListenerFunc func) :m_owner(owner), m_func(func) {}

	virtual void Call(Args... args) override
	{
		m_owner->*m_func(args...);
	}

	virtual bool operator==(const NotifyClassItem<T, Args...>& rhs) override
	{
		return m_owner == rhs.m_owner && m_func == rhs.m_func;
	}
private:
	T* m_owner;
	ListenerFunc m_func;
};

template<typename ...Args>
class NotifyFuncItem : public ListenerItem<Args...>
{
public:
	typedef std::function<void(Args...)> ListenerFunc;
	NotifyFuncItem(ListenerFunc func) :m_func(func) {}

	virtual void Call(Args... args)
	{
		m_func(args...);
	}

	virtual bool operator==(const NotifyFuncItem<Args...>& rhs) override
	{
		return m_func == rhs.m_func;
	}
private:
	ListenerFunc m_func;
};

template<typename ...Args>
class Notify : public Ref
{
public:
	typedef ListenerItem<Args...> ItemType;
	Notify() = default;
	~Notify()
	{
		this->m_items.clear();
	}

	void add(const ItemType* item)
	{
		m_items.push_back(item);
	}

	void remove(ItemType* item)
	{
		for (auto it = m_items.begin(); it != m_items.end();)
		{
			if ((*it) == item)
			{
				it = m_items.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void emit(const Args& ... args)
	{
		for (auto item : this->m_items)
		{
			item->Call(args...);
		}
	}
protected:
	std::vector<ItemType*> m_items;
};

END_OGS_NAMESPACE