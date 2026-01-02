#include "OpenGLContext.h"
#include "Core/Base.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	GFX_ASSERT(windowHandle, "Window handle is null!")
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	GFX_ASSERT(status, "Failed to initialize Glad!");


	GFX_INFO("OpenGL Info:");
	GFX_INFO("  Vendor: {0}",	(char*)glGetString(GL_VENDOR));
	GFX_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
	GFX_INFO("  Version: {0}",  (char*)glGetString(GL_VERSION));

}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
