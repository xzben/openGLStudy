#ifndef __2022_03_25_LIGHT_H__
#define __2022_03_25_LIGHT_H__

#include "common.h"
#include "base/Node.h"
#include "render/Color.h"
#include "math/Vec3.h"

BEGIN_NAMESPACE

struct LightShaderData
{
	POSITION pos;
	RGB		 ambient;
	RGB		 diffuse;
	RGB		 specular;

	fVec3    strength;
};

class Light : public Node
{
protected:
	Color			m_lightColor;
	bool			m_unitColor;
	LightShaderData m_lightInfo;
public:
	CREATE_FUNC(Light);
	Light();
	virtual ~Light();

	virtual void onLoad() override;
	void setLightColor(const Color& color);
	const Color& getLightColor() const;

	void setAmbientColor(const RGB& color);
	const RGB& getAmbientColor() const;

	void setDiffuseColor(const RGB& color);
	const RGB& getDiffuseColor() const;

	void setSpecularColor(const RGB& color);
	const RGB& getSpecularColor() const;

	const LightShaderData& getLightShaderData();

	float getAmbientStrength() { return m_lightInfo.strength.x; }
	void setAmbientStrength(float strength) { m_lightInfo.strength.x = strength; }

	float getSpecularStrength() { return m_lightInfo.strength.z; }
	void setSpecularStrength(float strength) { m_lightInfo.strength.z = strength; }

	float getDiffuseStrength() { return m_lightInfo.strength.y; }
	void setDiffuseStrength(float strength) { m_lightInfo.strength.y = strength; }

	virtual const Color& getDrawColor() override { return m_lightColor; }
};

END_NAMESPACE
#endif//__2022_03_25_LIGHT_H__