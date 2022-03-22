#ifndef __2022_03_22_MAERIAL_H__
#define __2022_03_22_MAERIAL_H__

#include "base/Object.h"
#include "common.h"

BEGIN_NAMESPACE

class Texture;
class Shader;

class Material : public Object
{
protected:
	Texture* m_texture;
	Shader* m_shader;
public:
	Material(Shader* shader);
	Material(int shaderId);

	virtual ~Material();


};

END_NAMESPACE

#endif//__2022_03_22_MAERIAL_H__