#pragma once

#include "editor_common.h"

namespace OGS
{
	class AssetModel;
}
BEGIN_EDITOR_NAMESPACE

class ModelImportHelper
{
public:
	OGS::AssetModel* GetModelFromFile(const std::string& filepath);
};

END_EDITOR_NAMESPACE