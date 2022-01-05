#include "render/RenderableComponent.h"
#include "render/config.h"

class RenderMesh : public RenderableComponent
{
protected:
	VAO_HANDLE m_va;
public:
	CREATE_FUNC(RenderMesh);
	RenderMesh();
	virtual ~RenderMesh();
	virtual void render() override;
};