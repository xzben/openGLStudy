#pragma once

#include "define.h"
#include "core/math/math.h"

BEGIN_OGS_NAMESPACE
struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	Matrix4 offset;
};

END_OGS_NAMESPACE