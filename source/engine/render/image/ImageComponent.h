#ifndef __IMAGE_2021_09_07_H__
#define __IMAGE_2021_09_07_H__


#include "common.h"
#include "render/config.h"
#include "render/RenderableComponent.h"

class Texture;
class Shader;

class ImageComponent : public RenderableComponent {
protected:
	Texture* m_texture;
	VAO_HANDLE m_vao;
	Shader* m_shader;
public:
	virtual void render();
	ImageComponent(const std::string& filename);
	ImageComponent();
	~ImageComponent();

	bool init(const std::string& filename);
	
	int getWidth();
	int getHeight();
	int getChannels();
};
#endif//__IMAGE_2021_09_07_H__