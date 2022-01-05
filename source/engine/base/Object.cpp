#include "Object.h"

Object::Object() 
	:m_refCount(1)
{

}

Object::~Object() 
{

}

void Object::addRef() 
{
	m_refCount++;
}

void Object::delRef() 
{
	CC_ASSET(m_refCount > 0);

	m_refCount--;

	if (m_refCount <= 0) 
	{
		delete this;
	}
}