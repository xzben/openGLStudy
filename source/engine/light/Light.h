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
	Color m_lightColor;
	float m_ambientStrength; //环境光强度
	float m_specularStrength; //镜面光强度
public:
	CREATE_FUNC(Light);
	Light();
	virtual ~Light();

	virtual void onLoad() override;
	void setLightColor(const Color& color);
	const Color& getLightColor();
	POSITION getLightPos();
	float getAmbientStrength() { return m_ambientStrength; }
	void setAmbientStrength(float strength) { m_ambientStrength = strength; }

	float getSpecularStrength() { return m_specularStrength; }
	void setSpecularStrength(float strength) { m_specularStrength = strength; }

	virtual const Color& getDrawColor() override { return m_lightColor; }
};

END_NAMESPACE
#endif//__2022_03_25_LIGHT_H__