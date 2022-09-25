#pragma once

#include "common.h"
#include "Node.h"

BEGIN_OGS_NAMESPACE

class Scene : public Node
{
	DECLARE_CLASS(Scene)
	DECLARE_REFLEX_CLASS_FIELD(Scene)
public:
	static Scene* createDefaultScene();
	Scene();
};

END_OGS_NAMESPACE