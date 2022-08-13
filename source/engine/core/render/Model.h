#pragma once

#include "common.h"
#include "core/base/Ref.h"

BEGIN_OGS_NAMESPACE

class Mesh;

class Model : public Ref
{
public:
	Model();
	virtual ~Model();


private:
	std::vector<Mesh*> 
};
END_OGS_NAMESPACE