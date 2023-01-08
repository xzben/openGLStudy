#pragma once

#include "core/base/Component.h"
#include "core/components/Renderable.h"

BEGIN_OGS_NAMESPACE
class Mesh;

class MeshRender : public Renderable
{
public:

private:
	AutoRef<Mesh> m_mesh;
};
END_OGS_NAMESPACE