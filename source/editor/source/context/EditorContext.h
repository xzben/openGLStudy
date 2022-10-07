#pragma once
#include "editor_common.h"
#include "core/base/Object.h"
#include <unordered_map>
BEGIN_EDITOR_NAMESPACE

enum class EStyle
{
	CLASSIC_STYLE,
	DARK_STYLE,
	LIGHT_STYLE,
	DUNE_DARK,
	ALTERNATIVE_DARK,
};

class EditorContext : public OGS::Object
{
	DECLARE_RUNTIME_CLASS(EditorContext)
public:
	virtual void handleInit() override;
	void applyStyle(EStyle style);
	bool loadFont(const std::string& pid, const std::string& path, float fontsize);
	bool unloadFont(const std::string& pid);
	bool useFont(const std::string& pid);
	bool useDefaultFont();
	void setLayoutSaveFilename(const std::string& filepath);
private:
	std::unordered_map<std::string, ImFont*> m_fonts;
	std::string m_layoutSaveFilename{ "imgui.ini" };
};
END_EDITOR_NAMESPACE