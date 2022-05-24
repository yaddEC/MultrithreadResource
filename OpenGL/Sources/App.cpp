#include <App.h>
#include <chrono>



using namespace Core;


 App::~App()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void App::Init(AppInitializer init)
{

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//number of lights
	nbrOfDir = 0;
	nbrOfPoint = 1;
	nbrOfSpot =0;
	//directional
	//lights.push_back((new DirectionalLight(Vec3(0.05f, 0.05f, 0.05f), Vec3(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f,1), Vec3(0, -1, 0))));
	//lights.push_back((new DirectionalLight(Vec3(0.05f, 0.05f, 0.05f), Vec3(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f, 1), Vec3(-1, 0, 0))));
	//point
	//lights.push_back(new PointLight(Vec3(0, 4, -2), Vec3(0.05f, 0.05f, 0.05f), Vec3(0.8f, 0.8f, 0.8f), Vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09, 0.032));
	//spot
	//lights.push_back(new SpotLight(Vec3(0, 2, 0), Vec3(0, -1, 0), Vec3(0, 0,0), Vec3(1.f,1.f, 1.f), Vec3(0.1f, 0.1f, 1.0f), 1.0f, 0.09, 0.032, cos(rad(45.5f)), cos(rad(60.f))));
	// glfw window creation
	// --------------------
	window = glfwCreateWindow(init.width, init.height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, init.framebuffer_size_callback);
	
	// glad: load all OpenGL function pointerss
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void App::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


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
	processInput(window);
	camera.Update((float)glfwGetTime(), inputs);

	glUseProgram(shaderProgram);
	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(viewPosLoc,camera.from.x, camera.from.y, camera.from.z);
	unsigned int nbrOfDirLoc = glGetUniformLocation(shaderProgram, "nbrOfDir");
	glUniform1i(nbrOfDirLoc, nbrOfDir);
	unsigned int nbrOfPointLoc = glGetUniformLocation(shaderProgram, "nbrOfPoint");
	glUniform1i(nbrOfPointLoc, nbrOfPoint);
	unsigned int nbrOfSpotLoc = glGetUniformLocation(shaderProgram, "nbrOfSpot");
	glUniform1i(nbrOfSpotLoc, nbrOfSpot);


	unsigned int matDifLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	glUniform1i(matDifLoc, 0);
	unsigned int matSpecLoc = glGetUniformLocation(shaderProgram, "material.specular");
	glUniform1i(matSpecLoc, 1);
	unsigned int matShinLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	glUniform1f(matShinLoc, 64);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture);

	
	Mat4 projView = camera.GetProjection() * camera.GetView();
	
	for (int i = 0; i < lights.size(); i++)
	{
		lights[i]->Update(shaderProgram);
	}

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Update(projView, shaderProgram);
	}

	Vec3 lightDir = (Vec3(0, 2, 0)- Vec3(0,0,-2)).Normalize();
	float theta = dot(lightDir, Vec3(0, -1, 0));
	printf("%f\n", theta);


		// input
		// -----
		glfwPollEvents();
		processInput(window);



		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);

	
}