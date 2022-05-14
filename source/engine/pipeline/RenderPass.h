#ifndef __2022_04_18_RENDER_PASS_H__
#define __2022_04_18_RENDER_PASS_H__

#include "common.h"

BEGIN_NAMESPACE

class Pipeline;

class RenderPass
{
public:
	enum class PassSort {
		FAR_TO_LEAR, //��Զ����
		LEAR_TO_FAR, //�ӽ���Զ
		NOT_SORT, //��������
	};
protected:
	PassSort m_sort;
public:
	void render(Pipeline* pipeline);
};

END_NAMESPACE
#endif//__2022_04_18_RENDER_PASS_H__