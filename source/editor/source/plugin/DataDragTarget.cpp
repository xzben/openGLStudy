#pragma once

#include "editor_common.h"
#include "plugin/IPlugin.h"
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

template<typename T>
class DataDragTarget : public IPlugin
{
public:
	DataDragTarget(const std::string& id)
		: identifier(id)
	{}
	virtual void excute() override
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (!m_isHovered)
				HoverStartEvent.emit();

			m_isHovered = true;

			ImGuiDragDropFlags target_flags = 0;
			// target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something

			if (!showYellowRect)
				target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(identifier.c_str(), target_flags))
			{
				T data = *(T*)payload->Data;
				DataReceivedEvent.emit(data);
			}
			ImGui::EndDragDropTarget();
		}
		else
		{
			if (m_isHovered)
				HoverEndEvent.emit();

			m_isHovered = false;
		}
	}

	bool IsHovered() const
	{
		return m_isHovered;
	}
public:
	std::string identifier;
	OGS::Notify<T> DataReceivedEvent;
	OGS::Notify<> HoverStartEvent;
	OGS::Notify<> HoverEndEvent;
	bool showYellowRect = true;
private:
	bool m_isHovered;
};

END_EDITOR_NAMESPACE