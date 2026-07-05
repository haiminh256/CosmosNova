#include <Cosmos/Engine.h>
#include <Cosmos/Core/Log.h>
#include <Cosmos/Shader/Shader.h>
#include <Cosmos/Renderer/Renderer.h>
#include <Cosmos/Core/OpenGLDebugger.h>
#include <Cosmos/Vertex/VertexArray.h>
#include <Cosmos/Vertex/VertexBuffer.h>
#include <Cosmos/Vertex/ElementBuffer.h>
#include <Cosmos/Renderer/Camera.h>
#include <Cosmos/Math/Time.h>
#include <Cosmos/Renderer/Texture.h>
#include <Cosmos/Renderer/Transform.h>
#include <Cosmos/Vertex/Vertex.h>

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

	Cosmos::Vertex vertices[] =
	{
		{{ 0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 0
		{{-0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 1
		{{-0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 2
		{{ 0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 3

		// Back (-Z)
		{{ 0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 4
		{{-0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 5
		{{-0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 6
		{{ 0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 7

		// Left (-X)
		{{-0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 8
		{{-0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 9
		{{-0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 10
		{{-0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 11

		// Right (+X)
		{{ 0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 12
		{{ 0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 13
		{{ 0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 14
		{{ 0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 15

		// Top (+Y)
		{{-0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 16
		{{-0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 17
		{{ 0.5f,  0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 18
		{{ 0.5f,  0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}, // 19

		// Bottom (-Y)
		{{-0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // 20
		{{-0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // 21
		{{ 0.5f, -0.5f,  0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // 22
		{{ 0.5f, -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}  // 23
	};
	unsigned int indices[] =
	{
		// đáy
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20,
	};

	Cosmos::ElementBuffer ebo;
	Cosmos::VertexBuffer vbo;
	Cosmos::VertexArray vao;
	Cosmos::Texture Texture;
	Cosmos::Transform Transform;

	vao.Bind();
	vbo.Bind();
	vbo.LoadData(vertices, sizeof(vertices));
	ebo.Bind();
	ebo.LoadData(indices, sizeof(indices));
	vao.VertexAttribPointer(0, 3, sizeof(Cosmos::Vertex), offsetof(Cosmos::Vertex, Position));
	vao.VertexAttribPointer(1, 3, sizeof(Cosmos::Vertex), offsetof(Cosmos::Vertex, Color));
	vao.VertexAttribPointer(2, 2, sizeof(Cosmos::Vertex), offsetof(Cosmos::Vertex, TexCoord));

	Texture.Load("Assets/hoshino.png", true);

	Cosmos::Camera Camera(800, 600, glm::vec3(0.0f, 0.0f, 2.0f));
	Cosmos::Time Time;

	while (!App.ShouldClose()) {
		Renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		Renderer.Clear();
		float deltaTime = Time.getDeltaTime();

		Transform.Rotation.y += 50.0f * deltaTime;
		Shader.UseShader();
		Shader.SetMat4("model", Transform.GetModelMatrix());
		Camera.Matrix(45.0f, 0.1f, 100.0f, Shader, "camMatrix");
		Texture.Bind(0);
		Shader.SetInt("tex0", 0);
		Renderer.Draw(0, 36);

		Camera.HandleInputs(App.getWindow(), deltaTime);

		App.EventHandle();
		App.SwapBuffers();
	}
	Texture.Delete();
	Shader.DeleteShader();
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	App.Quit();
}