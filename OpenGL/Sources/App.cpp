#include <App.h>
#include <chrono>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace Core;

App::~App()
{
	glfwTerminate();
}

void App::Init(AppInitializer init)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	//number of lights
	nbrOfDir = 1;
	nbrOfPoint = 0;
	nbrOfSpot = 0;
	//---------------------------------------------------
	//directional (remove the //)
	//---------------------------------------------------
	lights.push_back((new DirectionalLight(Vec3(0.05f, 0.05f, 0.05f), Vec3(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f, 1), Vec3(0, -1, 0))));
	//lights.push_back((new DirectionalLight(Vec3(0.05f, 0.05f, 0.05f), Vec3(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f, 1), Vec3(-1, 0, 0))));
	//---------------------------------------------------
	//point (remove the //)
	//---------------------------------------------------
	//lights.push_back(new PointLight(Vec3(0, -2, -2), Vec3(0.05f, 0.05f, 0.05f), Vec3(0.8f, 0.8f, 0.8f), Vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09, 0.032));
	//---------------------------------------------------
	//spot (remove the //)
	//---------------------------------------------------
	//lights.push_back(new SpotLight(Vec3(0, -2, 0), Vec3(0, -1, 0), Vec3(0, 0,0), Vec3(1.f,0.f, 1.f), Vec3(0.1f, 0.1f, 1.0f), 0.01f, 0.09, 0.032, cos(rad(15.f)), cos(rad(17.f))));
	
	// glfw window creation
	window = glfwCreateWindow(init.width, init.height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, init.framebuffer_size_callback);

	// glad: load all OpenGL function pointerss
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(init.glDebutOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glEnable(GL_DEPTH_TEST);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
void App::processInput(GLFWwindow* window)
{
	//camera mouvment control
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.from = camera.from - camera.speed * camera.forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.from = camera.from + camera.speed * camera.forward;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.from = camera.from + camera.speed * camera.right;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.from = camera.from - camera.speed * camera.right;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.from = camera.from + camera.speed * camera.up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.from = camera.from - camera.speed * camera.up;


}

void App::Update(int shaderProgram, unsigned int VAO)
{
	//mouse camera control
	if (mouseCaptured) {
		glfwGetCursorPos(window, &newMouseY, &newMouseX);
		if (firstMouse)
		{
			mouseX = newMouseX;
			mouseY = newMouseY;
			firstMouse = false;
		}
		mouseDeltaX = (float)(newMouseX - mouseX);
		mouseDeltaY = (float)(mouseY - newMouseY);
		mouseX = newMouseX;
		mouseY = newMouseY;

		inputs.deltaX = mouseDeltaX;
		inputs.deltaY = mouseDeltaY;
	}

	camera.Update((float)glfwGetTime(), inputs);

	//push matrix/floats to shader
	glUseProgram(shaderProgram);
	glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), camera.from.x, camera.from.y, camera.from.z);

	glUniform1i(glGetUniformLocation(shaderProgram, "nbrOfDir"), nbrOfDir);
	glUniform1i(glGetUniformLocation(shaderProgram, "nbrOfPoint"), nbrOfPoint);
	
	glUniform1i(glGetUniformLocation(shaderProgram, "nbrOfSpot"), nbrOfSpot);
	glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuse"), 0);

	glUniform1i(glGetUniformLocation(shaderProgram, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 128);




	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Mat4 projView = camera.GetProjection() * camera.GetView();
	//Update the lights
	for (int i = 0; i < lights.size(); i++)
	{
		lights[i]->Update(shaderProgram);
	}
	//Update the meshes
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Update(projView, shaderProgram);
	}

	glfwPollEvents();
	//inputs
	processInput(window);
	//ImGUI windows
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Scene");
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->parent == nullptr)
		{
			if (ImGui::TreeNode(gameObjects[i]->name.c_str()))
			{
				for (int j = 0; j < gameObjects[i]->childrens.size(); j++)
				{
					if (ImGui::TreeNode(gameObjects[i]->childrens[j].name.c_str()))
					{

						ImGui::TreePop();
						ImGui::Separator();
					}
					
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
		}
	}
	ImGui::End();
	ImGui::Begin("Mouse Capture");
	ImGui::Text("Right click to capture/un-capture mouse");
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		if(!mouseCaptured)
		{
	
			mouseCaptured = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			inputs.deltaX = 0;
			inputs.deltaY = 0;
			firstMouse = true;
			mouseCaptured = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);


}

