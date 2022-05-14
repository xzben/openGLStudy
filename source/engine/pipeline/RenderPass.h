#ifndef __2022_04_18_RENDER_PASS_H__
#define __2022_04_18_RENDER_PASS_H__

#include "common.h"

BEGIN_NAMESPACE

class Pipeline;

class RenderPass
{
public:
	enum class PassSort {
		FAR_TO_LEAR, //从远到近
		LEAR_TO_FAR, //从近到远
		NOT_SORT, //无需排序
	};
protected:
	PassSort m_sort;
public:
	void render(Pipeline* pipeline);
};

END_NAMESPACE
#endif//__2022_04_18_RENDER_PASS_H__