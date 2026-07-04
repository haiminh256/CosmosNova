#include <Cosmos/Engine.h>
#include <Cosmos/Core/Log.h>
#include <Cosmos/Shader/Shader.h>
#include <Cosmos/Renderer/Renderer.h>
#include <Cosmos/Core/OpenGLDebugger.h>
#include <Cosmos/Vertex/VertexArray.h>
#include <Cosmos/Vertex/VertexBuffer.h>
#include <Cosmos/Vertex/ElementBuffer.h>

int main() {
	Cosmos::Engine App;
	if (!App.Init()) {
		App.Terminate();
	}
	App.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	App.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	App.SetWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	App.SetWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	App.CreateAppWindow(800, 600, "Engine Window");
	App.ApplyWindowHint();

	Cosmos::Renderer Renderer;
	Renderer.Init();
	Renderer.SetViewport(0,0,800,600);

	Cosmos::Shader Shader;
	Shader.CompileShader("Shader/vertex.glsl", "Shader/fragment.glsl");
	Shader.CreateShaderProgram();

	Cosmos::OpenGLDebugger::EnableDebug();

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Cosmos::ElementBuffer ebo;
	Cosmos::VertexBuffer vbo;
	Cosmos::VertexArray vao;

	vao.Bind();
	vbo.Bind();
	vbo.LoadData(vertices, sizeof(vertices));
	ebo.Bind();
	ebo.LoadData(indices, sizeof(indices));
	vao.VertexAttribPointer(0, 3, 3 * sizeof(float), 0);

	while (!App.ShouldClose()) {
		Renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		Renderer.Clear();

		Shader.UseShader();
		Renderer.Draw(0, 6);

		App.EventHandle();
		App.SwapBuffers();
	}
	Shader.DeleteShader();
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	App.Quit();
}