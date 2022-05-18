#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>
#include <Log.h>
#include <Model.h>
#include <Camera.h>


#include <iostream>
using namespace LowRenderer;
namespace Core
{
	struct AppInitializer
	{
		Camera cam;
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void(*glDebutOutput)(GLenum source, GLenum type, GLenum init, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam);
	};


	class App {

	public:
		~App();
		GLFWwindow* window;
		void Init(AppInitializer init);
		void Update(int shaderProgram, unsigned int VAO);
	};

}

