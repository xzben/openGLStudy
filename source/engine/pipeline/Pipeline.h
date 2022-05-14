#ifndef __2022_04_18_PIPELINE_H__
#define __2022_04_18_PIPELINE_H__

#include "common.h"
#include "base/Object.h"
#include "base/NonCopyable.h"

BEGIN_NAMESPACE

class Scene;

class Pipeline : public Object, public NonCopyable
{
protected:

public:
	Pipeline();
	virtual ~Pipeline();

	virtual void render(Scene* scene);
};

END_NAMESPACE
#endif//__2022_04_18_PIPELINE_H__