#pragma once

#include "common.h"
#include "core/base/Object.h"

BEGIN_OGS_NAMESPACE

class Mesh;

class Model : public Object
{
public:
	Model();
	virtual ~Model();


private:
	std::vector<Mesh*> 
};
END_OGS_NAMESPACE