#include "PlaneMesh.h"

BEGIN_NAMESPACE

static float plane_vertices[] = {
	//----- pos -------  |-------uv-------|----uv----| 
	5.0f,  -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f,

	5.0f,  -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f,
	5.0f,  -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f
};

PlaneMesh::PlaneMesh()
{
	setup(plane_vertices, 6, nullptr, 0, VerticleMember::POS_COLOR_TEXCOORD);
}

PlaneMesh::~PlaneMesh()
{

}

END_NAMESPACE