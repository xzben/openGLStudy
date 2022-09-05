#pragma once

#include "editor_common.h"
#include "core/reflex/reflex.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class EditorAsset : public OGS::Object
{
	DECLARE_CLASS(EditorAsset);
public:
	EditorAsset();
	virtual ~EditorAsset();
private:
	AssetType m_type;
};

END_EDITOR_NAMESPACE