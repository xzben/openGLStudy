#pragma once

#include "editor_common.h"
#include "plugin/IPlugin.h"
#include "core/base/Notify.h"
BEGIN_EDITOR_NAMESPACE

template<typename T>
class DataDragSource : public IPlugin
{
public:
	DataDragSource(const std::string& id, const std::string& tips, T d) 
		: identifier(id)
		, tooltip(tips)
		, data(d)
	{}
	virtual void excute() override
	{
		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging

		if (!hasTooltip)
			src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip

		if (ImGui::BeginDragDropSource(src_flags))
		{
			if (!m_isDragged)
				DragStartEvent.emit();

			m_isDragged = true;

			if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
				ImGui::Text(tooltip.c_str());
			ImGui::SetDragDropPayload(identifier.c_str(), &data, sizeof(data));
			ImGui::EndDragDropSource();
		}
		else
		{
			if (m_isDragged)
				DragStopEvent.emit();

			m_isDragged = false;
		}
	}

	bool IsDragged() const
	{
		return m_isDragged;
	}
public:
	std::string identifier;
	std::string tooltip;
	T data;

	OGS::Notify<> DragStartEvent;
	OGS::Notify<> DragStopEvent;
	bool hasTooltip = true;
private:
	bool m_isDragged;
};

END_EDITOR_NAMESPACE