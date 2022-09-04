#include "OGL3Device.h"
#include "glfw/glfw3.h"
#include "core/view/GameView.h"

BEGIN_OGS_NAMESPACE

void OGL3Device::swapFrameBuffer()
{
	glfwSwapBuffers(m_gameview->GetWindow());
}
END_OGS_NAMESPACE