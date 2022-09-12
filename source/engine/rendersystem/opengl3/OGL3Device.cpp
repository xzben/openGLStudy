#include "OGL3Device.h"
#include "glfw/glfw3.h"
#include "core/view/GameView.h"

BEGIN_OGS_NAMESPACE

static void glfw_error_callback(int error, const char* description)
{
	CCLOG_ERROR("Glfw Error %d: %s\n", error, description);
}


bool OGL3Device::init()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	return true;
}

void OGL3Device::processEvent()
{
	glfwPollEvents();
}

void OGL3Device::swapFrameBuffer()
{
	glfwSwapBuffers(m_gameview->GetWindow());
}

END_OGS_NAMESPACE