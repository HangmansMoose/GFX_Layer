#include "VertexArray.h"

#include "Renderer.h"
#include "GFX_APIs/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:    GFX_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
	}

	GFX_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}