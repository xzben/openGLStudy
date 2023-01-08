#include "AssetMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(SubMesh)

IMPLEMENT_CLASS(AssetMesh)

SubMesh::SubMesh()
{

}

SubMesh::~SubMesh()
{

}
void AssetMesh::onLoad(const AutoRef<Data>& data)
{

}

void AssetMesh::onUnload()
{

}
END_OGS_NAMESPACE