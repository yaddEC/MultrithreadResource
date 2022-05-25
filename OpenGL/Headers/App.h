#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>
#include <Log.h>
#include <Model.h>
#include <Camera.h>
#include <Mesh.h>
#include <Light.h>
#include <GameObject.h>
#include <iostream>
using namespace LowRenderer;
namespace Core
{
	struct AppInitializer
	{
		
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
		App() {};
		bool mouseCaptured = false;
		int nbrOfDir ;
		int nbrOfPoint;
		int nbrOfSpot ;
		bool firstMouse = true;
		std::vector<Mesh*> meshes;
		std::vector<GameObject*> gameObjects;
		Camera camera;
		CameraInputs inputs;
		std::vector<Light*> lights;
		double mouseX = 0.0;
		double mouseY = 0.0;
		float mouseDeltaX = 0.0;
		float mouseDeltaY = 0.0;

		double newMouseX, newMouseY;
		GLFWwindow* window;
		void Init(AppInitializer init);
		void Update(int shaderProgram, unsigned int VAO);
		void processInput(GLFWwindow* window);
	};

}

