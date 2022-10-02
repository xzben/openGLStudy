#include "EditorWindow.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/view/GameView.h"
#include "EditorApp.h"
#include "EditorMenuBar.h"
#include "EditorFrame.h"
#include "event/EditorEventMgr.h"
USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorWindow)

EditorWindow::EditorWindow()
{

}

EditorWindow::~EditorWindow()
{
	uninitEvent();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	m_frames.clear();
}

bool EditorWindow::init(OGS::GameView* view)
{
	m_gameview = view;
	if (!initContext())
		return false;

	if (!initUI())
		return false;

	initEvent();

	return true;
}

bool  EditorWindow::initUI()
{
	setupMenuBar();
	setupFrames();

	return true;
}

void EditorWindow::initEvent()
{
	EditorEventMgr::GetInstance()->getNotifybyEvent(EditorEvent::FRAME)->subscribe(this, &EditorWindow::handleFrameEvent);
}

void EditorWindow::uninitEvent()
{
	EditorEventMgr::GetInstance()->getNotifybyEvent(EditorEvent::FRAME)->unsubscribe(this, &EditorWindow::handleFrameEvent);
}

bool  EditorWindow::initContext()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	io.ConfigDockingAlwaysTabBar = true;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(1.0, 0);
	style.FramePadding = ImVec2(14.0, 2.0f);
	style.ChildBorderSize = 0.0f;
	style.FrameRounding = 5.0f;
	style.FrameBorderSize = 1.5f;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(m_gameview->GetWindow(), true);
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
#endif
	ImGui_ImplOpenGL3_Init(glsl_version);

	
	return true;
}

void EditorWindow::preRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EditorWindow::defaultLaytout(int dockspace_id)
{
	ImGuiID left;
	ImGuiID left_top;
	ImGuiID left_bottom;
	ImGuiID center;
	ImGuiID center_top;
	ImGuiID center_bottom;
	ImGuiID right;
	ImGuiID temp;
	ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.25, &right, &temp);
	ImGui::DockBuilderSplitNode(temp, ImGuiDir_Left, 0.3, &left, &center);

	ImGui::DockBuilderSplitNode(left, ImGuiDir_Up, 0.7, &left_top, &left_bottom);
	ImGui::DockBuilderSplitNode(center, ImGuiDir_Up, 0.7, &center_top, &center_bottom);
	
	this->m_spaceId2GuiId.insert(std::make_pair(MainDockSpace::LEFT_TOP, left_top));
	this->m_spaceId2GuiId.insert(std::make_pair(MainDockSpace::LEFT_BOTTOM, left_bottom));
	this->m_spaceId2GuiId.insert(std::make_pair(MainDockSpace::CENTER_TOP, center_top));
	this->m_spaceId2GuiId.insert(std::make_pair(MainDockSpace::CENTER_BOTTOM, center_bottom));
	this->m_spaceId2GuiId.insert(std::make_pair(MainDockSpace::RIGHT, right));
}

ImGuiID EditorWindow::getDockspaceId(MainDockSpace spaceid)
{
	if (!m_isInitDock)
		return 0;
	return m_spaceId2GuiId[spaceid]; 
}

void EditorWindow::renderMainDockSpace()
{
	//默认main dockspace 只能允许子节点上下左右防止，不允许中间放置
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_DockSpace;
	ImGuiWindowFlags   window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
		ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBringToFrontOnFocus;

	// fullscreen setting
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	int width, height;
	m_gameview->getWindowSize(width, height);

	ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(viewport->WorkSize, ImGuiCond_Always);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("MainDockspace", nullptr, window_flags);
	ImGuiID main_docking_id = ImGui::GetID("MainDockspace");
	m_isInitDock = false;
	if (ImGui::DockBuilderGetNode(main_docking_id) == nullptr)
	{
		m_isInitDock = true;
		ImGui::DockBuilderRemoveNode(main_docking_id);
		ImGui::DockBuilderAddNode(main_docking_id, dockspace_flags);
		ImGui::DockBuilderSetNodePos(main_docking_id,
			ImVec2(viewport->WorkPos.x, viewport->WorkPos.y));
		ImGui::DockBuilderSetNodeSize(main_docking_id,
			ImVec2((float)width, (float)height));

		defaultLaytout(main_docking_id);
		ImGui::DockBuilderFinish(main_docking_id);
	}

	ImGui::DockSpace(main_docking_id);
	ImGui::End();
}

void EditorWindow::render()
{
	m_menubar->render();
	renderMainDockSpace();
	for (auto it : m_frames)
	{
		ImGuiID spaceid = this->getDockspaceId(it.config.spaceid);
		it.frame->setDockspace(spaceid);
		it.frame->render();
	}
}

void EditorWindow::postRender()
{
	ImGui::Render();
}

void EditorWindow::draw()
{
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int display_w, display_h;
	glfwGetFramebufferSize(m_gameview->GetWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void EditorWindow::showFrame(EditorFrame* frame)
{

}
void EditorWindow::closeFrame(EditorFrame* frame)
{

}

END_EDITOR_NAMESPACE