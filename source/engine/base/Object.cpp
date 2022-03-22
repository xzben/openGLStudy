#include "Object.h"

BEGIN_NAMESPACE

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
	CC_ASSERT(m_refCount > 0);

	m_refCount--;

	if (m_refCount <= 0) 
	{
		delete this;
	}
}

END_NAMESPACE