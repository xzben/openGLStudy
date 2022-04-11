#ifndef __2022_04_11_TEXTURE_CUBE_H__
#define __2022_04_11_TEXTURE_CUBE_H__

#include "common.h"
#include "render/Texture.h"

BEGIN_NAMESPACE

class TextureCube : public Texture
{
protected:
	GL_HANDLE m_texture;

public:
	TextureCube();
	virtual ~TextureCube();

	bool init(std::string faces[6]);

	virtual void use(int index = 0);
	virtual void unuse();
};

END_NAMESPACE
#endif//__2022_04_11_TEXTURE_CUBE_H__