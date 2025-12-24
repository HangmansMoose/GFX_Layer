#include "Core/Window.h"
#include "Core/Base.h"
#include "Platform/Win32Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

int main()
{
	Log::Init();
	
	if (!glfwInit())
	{
		GFX_ERROR("Failed to initialise GLFW. Exiting...\n");
	}
	WindowProps winProps;
	

	Window* window = new WindowsWindow(winProps);

	std::shared_ptr<VertexArray> vertArray;
	std::shared_ptr<Shader> shader;
	
	std::shared_ptr<Shader> blueShader;
	std::shared_ptr<VertexArray> squareVertArray;

	vertArray.reset(VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	std::shared_ptr<VertexBuffer> vertBuffer;
	vertBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	BufferLayout bufLayout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" }
	};

	vertBuffer->SetLayout(bufLayout);
	vertArray->AddVertexBuffer(vertBuffer);
	
	u32 indices[3] = { 0, 1, 2 };
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(u32)));
	vertArray->SetIndexBuffer(indexBuffer);

	squareVertArray.reset(VertexArray::Create());
	
	float squareVertices[3 * 4] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f
	};

	std::shared_ptr<VertexBuffer> squareVertexBuffer;
	squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVertexBuffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position" }
		});
	squareVertArray->AddVertexBuffer(squareVertexBuffer);

	u32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<IndexBuffer> squareIndexBuffer;
	squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(u32)));
	squareVertArray->SetIndexBuffer(squareIndexBuffer);

	// Quick side note, in modern C++ you can simply enclose multi line strings in R"()"
	// Much, Much nicer than it used to be
	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		blueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

		bool running = true;

		while (running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			blueShader->Bind();
			Renderer::Submit(squareVertArray);

			shader->Bind();
			Renderer::Submit(vertArray);

			Renderer::EndScene();

			window->OnUpdate();
		}
}