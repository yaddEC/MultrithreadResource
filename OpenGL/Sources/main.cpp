
#include <Log.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

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
	AppInitializer initialiser = {SCR_WIDTH, SCR_HEIGHT, 4, 5, "Chayen", framebuffer_size_callback, glDebugOutput};
	App app;
	app.Init(initialiser);
	Log log;
	log.OpenFile("test.txt");
	
	
	
	ASSERT(true,"Assertion test \n");

	DEBUG_LOG(" DebugLog Test \n");

	Shader shader;
	Model* cube;
	Model* model;
	ResourceManager resources;

	auto begin = std::chrono::high_resolution_clock::now();
	resources.Create<Model>("Resources/Obj/cube.obj");
	resources.Create<Model>("Resources/Obj/fe.obj");
	cube = resources.Get<Model>("Resources/Obj/cube.obj");
	model = resources.Get<Model>("Resources/Obj/fe.obj");
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.62f seconds.\n", elapsed.count() * 1e-9);
	//cube->Print();
	
	app.meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(Vec3(0, 0, 0), Vec3(0, 0,0), Vec3(10, 1,10))));
	app.meshes.push_back(new Mesh(model, Mat4().CreateTransformMatrix(Vec3(1, 0, 0), Vec3(-4, 8, -4), Vec3(0.5, 0.5, 0.5))));
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	shader.SetVertexShader("Resources/Shaders/vertexShader.glsl");
	// fragment shader
	shader.SetFragmentShader("Resources/Shaders/fragmentShader.glsl");
	// link shaders
	shader.Link();

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	

	

	// glGenBuffers(1, &VBO);





	// generate the texture data
	// ------------------------------------
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("sample.png", &width, &height, &nrChannels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(data);

	data = stbi_load("sample2.png", &width, &height, &nrChannels, 0);

	GLuint texture2;

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(data);


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


	glBindTextureUnit(0, texture);
	glBindSampler(0, sampler);

	glBindTextureUnit(1, texture2);
	glBindSampler(1, sampler);



	
	while (!glfwWindowShouldClose(app.window))
	{
		app.Update(shader.shaderProgram, cube->vao.vao);

	}



	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------


	glDeleteTextures(1, &texture);

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