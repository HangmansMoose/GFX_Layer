#pragma once

#include "Core/GfxContext.h"

struct GLFWwindow;

class OpenGLContext : public GfxContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);

	virtual void Init() override;
	virtual void SwapBuffers() override;
private:
	GLFWwindow* m_WindowHandle;
};