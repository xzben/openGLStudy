#ifndef __IMAGE_2021_09_07_H__
#define __IMAGE_2021_09_07_H__


#include "common.h"
#include "render/config.h"
#include "render/RenderableComponent.h"
#include "math/Mat4.h"

BEGIN_NAMESPACE

class Texture;
class Shader;
class Mesh;

class ImageComponent : public RenderableComponent 
{
protected:
	Texture* m_texture;
	Shader* m_shader;
	Mesh* m_mesh;
public:
	virtual void render() override;
	ImageComponent(const std::string& filename);
	ImageComponent();
	~ImageComponent();

	bool init(const std::string& filename);
	
	int getWidth();
	int getHeight();
	int getChannels();
};

END_NAMESPACE
#endif//__IMAGE_2021_09_07_H__