
#include <Log.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <App.h>
#include <Shader.h>

using namespace Core;
using namespace Debug;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{

	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{

	//Create/Initialise the App window
	AppInitializer initialiser = { SCR_WIDTH, SCR_HEIGHT, 4, 5, "Chayen", framebuffer_size_callback, glDebugOutput };
	App app;
	app.Init(initialiser);
	
	Log log;
	log.OpenFile("test.txt");

	ASSERT(true, "Assertion test \n");

	DEBUG_LOG(" DebugLog Test \n");

	Shader shader;
	Model* cube;
	Model* model;
	ResourceManager resources;

	auto begin = std::chrono::high_resolution_clock::now();
	resources.Create<Model>("Resources/Obj/cube.obj");
	resources.Create<Model>("Resources/Obj/malbazar.obj");
	cube = resources.Get<Model>("Resources/Obj/cube.obj");
	model = resources.Get<Model>("Resources/Obj/malbazar.obj");
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.62f seconds.\n", elapsed.count() * 1e-9);
	//print the vertices in the console
	//cube->Print();
	
	//create the meshes
	app.meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(Vec3(0, 0, 0), Vec3(0, -5, 0), Vec3(10, 1, 10)), "sample.png"));
	app.meshes.push_back(new Mesh(model, Mat4().CreateTransformMatrix(Vec3(0, 180, 0), Vec3(0, -2, 0), Vec3(0.01, 0.01, 0.01)), "Resources/Textures/malbazar.png"));
	app.meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(Vec3(1, 0, 0), Vec3(0, 3, -4), Vec3(0.5, 0.5, 0.5)), "sample2.png"));

	//link them to gameObjects
	app.gameObjects.push_back(new GameObject("cube chat", app.meshes[0]));
	app.gameObjects.push_back(new GameObject("cube chien", app.meshes[2], app.gameObjects[0]));//this one has 'cube chat' as a parent
	app.gameObjects.push_back(new GameObject("malbazar", app.meshes[1]));


	for (int i = 0; i < app.gameObjects.size(); i++)
	{
		if (app.gameObjects[i]->parent != nullptr)
		{
			app.gameObjects[i]->parent->childrens.push_back(*app.gameObjects[i]);
		}
	}
	// build and compile our shader program
	// 
	// vertex shader
	shader.SetVertexShader("Resources/Shaders/vertexShader.glsl");
	// fragment shader
	shader.SetFragmentShader("Resources/Shaders/fragmentShader.glsl");
	// link shaders
	shader.Link();

	// create a sampler and parameterize it
	// ------------------------------------
	GLuint sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	glBindSampler(0, sampler);

	while (!glfwWindowShouldClose(app.window))
	{
		app.Update(shader.shaderProgram, cube->vao.vao);
	}

	for (int i = 0; i < app.meshes.size(); i++)
		glDeleteTextures(1, &app.meshes[i]->texture);

	glDeleteSamplers(1, &sampler);


	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}