#ifndef __2022_04_15_CUBE_H__
#define __2022_04_15_CUBE_H__

#include "base/Node.h"
#include "common.h"

BEGIN_NAMESPACE
class Plane : public Node
{
public:
	CREATE_FUNC(Plane);

	static Plane* createColorMaterial();
	static Plane* createSampleMaterial();

	Plane();
	virtual ~Plane();

	virtual void onLoad() override;
};

END_NAMESPACE
#endif//__2022_03_31_CUBE_H__#pragma once
