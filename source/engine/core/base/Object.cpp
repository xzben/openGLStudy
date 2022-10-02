#include "Object.h"
#include "core/ptr/WeakRef.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS_BASE(Object);

Object::Object()
{

}

Object::~Object()
{
	ASSERT(m_refcount == 0, "must been 0 when delete");
}

void Object::release()
{
	if (m_linker)
	{
		m_linker->m_obj = nullptr;
		if (m_linker->m_weakcount <= 0)
		{
			delete m_linker;
			m_linker = nullptr;
		}
	}

	delete this;
}
WeakLinker* Object::getLinker()
{
	if (m_linker)
	{
		return m_linker;
	}

	m_linker = new WeakLinker();
	m_linker->m_obj = this;

	return m_linker;
}
END_OGS_NAMESPACE