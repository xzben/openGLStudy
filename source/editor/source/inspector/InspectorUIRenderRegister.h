#pragma once

#include "editor_common.h"

BEGIN_EDITOR_NAMESPACE

class InspectorUIMgr;

void registerCommonInspectorUI(InspectorUIMgr* mgr);
void registerNodeUIRender(InspectorUIMgr* mgr);

END_EDITOR_NAMESPACE