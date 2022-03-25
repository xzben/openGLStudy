#ifndef __2022_03_25_LIGHT_H__
#define __2022_03_25_LIGHT_H__

#include "common.h"
#include "base/Node.h"

BEGIN_NAMESPACE

class Light : public Node
{
public:
	Light();
	virtual ~Light();
};

END_NAMESPACE
#endif//__2022_03_25_LIGHT_H__