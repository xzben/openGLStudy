#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_OGS_NAMESPACE
class Asset;
class Node;
class Object;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE

class InspectorFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(InspectorFrame)
public:
	InspectorFrame(){}
protected:
	void handleInit() override;
	void updateView(OGS::Object* obj);
private:
	AutoRef<OGS::Object> m_showObject{ nullptr };
};
END_EDITOR_NAMESPACE