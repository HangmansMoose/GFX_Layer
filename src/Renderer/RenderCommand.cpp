#include "RenderCommand.h"


#include "GFX_APIs/OpenGL/OpenGLRendererAPI.h"

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
