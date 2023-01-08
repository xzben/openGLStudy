#include "TextureCube.h"
#include<stb_image.h>
#include <glad/glad.h>
#include <iostream>

BEGIN_NAMESPACE

TextureCube::TextureCube()
{
	glGenTextures(1, &m_texture);
}

TextureCube::~TextureCube()
{
	glDeleteTextures(1, &m_texture);
}

/*
0 - right  
1 - left 
2 - top 
3 - bottom 
4 - front 
5 - back
*/
bool TextureCube::init(std::string faces[6])
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	int width, height, nrChannels;

	for (int i = 0; i < 6; i++)
	{
		Data data;
		if (!FileUtils::getInstance()->getData(faces[i].c_str(), &data))
			return false;

		unsigned char* img_data = stbi_load_from_memory(data.getContent(),
			data.getContentSize(),
			&width,
			&height,
			&nrChannels,
			0);
		if (img_data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data
			);
			stbi_image_free(img_data);
		}
		else
		{
			std::cout << "cube map texture failed to load at path: " << faces[i] << std::endl;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}


void TextureCube::use(int index /*= 0*/)
{
	CC_ASSERT(index >= 0 && index <= 31);

	m_useIndex = index;
	//ÉèÖÃÎÆÀíindex
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_texture);
}

void TextureCube::unuse()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
END_NAMESPACE