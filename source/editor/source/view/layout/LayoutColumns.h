#pragma once

#include "editor_common.h"
#include "view/UIContainor.h"
#include <array>
#include <string>
BEGIN_EDITOR_NAMESPACE

template<int _Size>
class LayoutColumns : public EditorUIContainor
{
	DECLARE_RUNTIME_TEMPLATE_CLASS(LayoutColumns, _Size)
public:
	LayoutColumns()
	{
		widths.fill(-1.f);
	}
protected:
	virtual bool onRender()
	{
		ImGui::Columns(_Size, m_guid.c_str(), border);
		int counter = 0;

		for (auto it = m_childrens.begin(); it != m_childrens.end();)
		{
			(*it)->render();

			++it;

			if (it != m_childrens.end())
			{
				if (widths[counter] != -1.f)
				{
					ImGui::SetColumnWidth(counter, widths[counter]);
				}

				ImGui::NextColumn();
			}

			++counter;
			if (counter == _Size)
				counter = 0;
		}
		ImGui::Columns(1); //
		return true;
	}
public:
	std::array<float, _Size> widths;
	bool border{ false };
};

constexpr const char* templateNames[] = {
	"LayoutColumns<1>",
	"LayoutColumns<2>",
	"LayoutColumns<3>",
	"LayoutColumns<4>",
	"LayoutColumns<5>",
	"LayoutColumns<6>",
	"LayoutColumns<7>",
	"LayoutColumns<8>",
	"LayoutColumns<9>",
	"LayoutColumns<10>",
	"LayoutColumns<11>",
	"LayoutColumns<12>",
};

template<int _Size>
OGS::Runtime LayoutColumns<_Size>::RuntimeLayoutColumnsObj(templateNames[_Size], LayoutColumns<_Size>::Super::GetRUNTIME());


END_EDITOR_NAMESPACE