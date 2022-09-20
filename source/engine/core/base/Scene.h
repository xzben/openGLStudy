#pragma once

#include "common.h"
#include "Object.h"
#include "NodeContainor.h"

BEGIN_OGS_NAMESPACE

class Scene : public NodeContainor,  public Object
{
	DECLARE_CLASS(Scene)
	DECLARE_REFLEX_CLASS_FIELD(Scene)
public:
	static Scene* createDefaultScene();
	Scene();

protected:
	std::string m_name;
};

END_OGS_NAMESPACE