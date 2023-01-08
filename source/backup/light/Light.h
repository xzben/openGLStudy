#ifndef __2022_03_25_LIGHT_H__
#define __2022_03_25_LIGHT_H__

#include "common.h"
#include "base/Node.h"
#include "render/Color.h"
#include "math/Vec3.h"

BEGIN_NAMESPACE

class Light : public Node
{
protected:
	Color			m_lightColor;
	Light();
	virtual ~Light();
public:
	virtual void doStart() override;
	virtual void doStop() override;
	virtual void doLoad() override;

	virtual void setShaderLightInfo(Shader* shader, int index) = 0;

	void setLightColor(const Color& color);
	const Color& getLightColor() const;

	virtual const Color& getDrawColor() override { return m_lightColor; }
};

END_NAMESPACE
#endif//__2022_03_25_LIGHT_H__