#ifndef __2021_12_29_OBJECT_H__
#define __2021_12_29_OBJECT_H__

#include "common.h"

class Object 
{
protected:
	int m_refCount;
public:
	Object();
	virtual ~Object();
	
	void addRef();
	void delRef();
};
#endif//__2021_12_29_OBJECT_H__