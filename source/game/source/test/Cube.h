#ifndef __2022_03_31_CUBE_H__
#define __2022_03_31_CUBE_H__

#include "base/Node.h"
#include "common.h"

BEGIN_NAMESPACE
class Cube : public Node
{
public:
	CREATE_FUNC(Cube);
	
	static Cube* createColorMaterial();
	static Cube* createSampleMaterial();

	Cube();
	virtual ~Cube();

	virtual void onLoad() override;
};

END_NAMESPACE
#endif//__2022_03_31_CUBE_H__