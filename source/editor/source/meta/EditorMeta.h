#pragma once

#include "editor_common.h"
#include "core/reflex/reflex.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class EditorMeta
{
	DECLARE_CLASS_BASE(EditorMeta)
public:
	EditorMeta();
	virtual ~EditorMeta();


protected:
	GUID m_guid;
};
END_EDITOR_NAMESPACE