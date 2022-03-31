#ifndef __2021_12_29_OBJECT_H__
#define __2021_12_29_OBJECT_H__

#include "common.h"

BEGIN_NAMESPACE

class Object
{
protected:
	int m_refCount;
public:
	Object();
	virtual ~Object();

	void addRef();
	void delRef();
	int  getRef();
};

END_NAMESPACE

#endif//__2021_12_29_OBJECT_H__