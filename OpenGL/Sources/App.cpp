#include <App.h>
#include <chrono>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace Core;


static volatile int iter = 0;

//(o.luanda):Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


App::~App()
{
	resourceThread.detach();
	UnloadData();
	glfwTerminate();
}


void App::ProcessThreadResource(std::vector<ModelAttribute> attribs)
{
	while (iter < attribs.size())
	{

#if 0 //(o.luanda):this part do what AddModel does
		ModelAttribute* attrib = &attribs[iter];
	
		mResourceManager->Create<Model>(attrib->filePath);
		models.push_back(mResourceManager->Get<Model>(attrib->filePath));

		Model* cube = models[iter];
		meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(attrib->rotation, attrib->position,
			attrib->scale), attrib->texPath.c_str()));

		this->gameObjects.push_back(new GameObject(attrib->name, this->meshes[iter]));
#endif
		AddModel(attribs);

		iter++;
	}
}


void App::AddModel(std::vector<ModelAttribute> attribs)
{
	ModelAttribute* attrib = &attribs[iter];

	mResourceManager->Create<Model>(attrib->filePath);
	models.push_back(mResourceManager->Get<Model>(attrib->filePath));

	Model* cube = models[iter];
	meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(attrib->rotation, attrib->position,
		attrib->scale), attrib->texPath.c_str()));

	this->gameObjects.push_back(new GameObject(attrib->name, this->meshes[iter]));

}


void App::InitSampler()
{
	sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	glBindSampler(0, sampler);
}

#if 0
bool App::LoadData()
{

	mResourceManager->Create<Model>("../assets/cube.obj");
	cube = mResourceManager->Get<Model>("../assets/cube.obj");

	mResourceManager->Create<Model>("../assets/malbazar.obj");
	model = mResourceManager->Get<Model>("../assets/malbazar.obj");

	this->meshes.push_back(new Mesh(cube, Mat4().CreateTransformMatrix(Vec3(M_PI / 4.0f, 0, 0), Vec3(0, -1, 0), Vec3(2, 1, 2)), "../assets/Cube.png"));
	this->gameObjects.push_back(new GameObject("cube chat", this->meshes[0]));


	this->meshes.push_back(new Mesh(model, Mat4().CreateTransformMatrix(Vec3(0, 270, 0), Vec3(0, 1, 0), Vec3(0.01, 0.01, 0.01)), "../assets/malbazar.png"));
	this->gameObjects.push_back(new GameObject("malbazar", this->meshes[1]));

	InitSampler();

	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		if (this->gameObjects[i]->parent != nullptr)
		{
			this->gameObjects[i]->parent->childrens.push_back(*gameObjects[i]);
		}
	}


	return true;

}
#endif

void App::UnloadData()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		glDeleteTextures(1, &meshes[i]->texture);
	}
	glDeleteSamplers(1, &sampler);

	mResourceManager->Unload();
	delete mResourceManager;
}

bool App::LoadShaders()
{
	if (!shader.SetVertexShader("Resources/Shaders/vertexShader.glsl") ||
		!shader.SetFragmentShader("Resources/Shaders/fragmentShader.glsl"))
	{
		return false;
	}
	shader.Link();

	return true;
}

bool App::Init(AppInitializer init)
{
	mResourceManager = new ResourceManager();
	if (!mResourceManager)
	{
		std::cout << "Failed to initialize resource Manager" << std::endl;
		return false;
	}

	std::vector<ModelAttribute> attribs;
	attribs.push_back({ std::string("Resources/Obj/cube.obj"), std::string("Cube"),std::string("Resources/Textures/Cube.png"),
		{0.0f, -1.0f, 0.0f},{M_PI / 4.0f, 0.0f, 0.0f},{2.0f, 1.0f, 2.0f} });

	attribs.push_back({ std::string("Resources/Obj/malbazar.obj"), std::string("malbazar"),std::string("Resources/Textures/malbazar.png"),
		{0.0f, 1.0f, 0.0f},{0.0f, 270.0f, 0.0f},{0.01f, 0.01f, 0.01f} });

	new (&resourceThread) std::thread(&App::ProcessThreadResource, this, attribs);




	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	//number of lights
	nbrOfDir = 1;
	nbrOfPoint = 0;
	nbrOfSpot = 0;

	lights.push_back((new DirectionalLight(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.5f, 0.5f, 0.5f), Vec3(1.0f, 1.0f, 1), Vec3(0, -1, 0))));

	window = glfwCreateWindow(init.width, init.height, "Game Programming", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, init.framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
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

	InitSampler();
	glEnable(GL_DEPTH_TEST);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//------------(o.luanda)-----------------



	if (!LoadShaders())
	{
		std::cout << "Failed to load shaders." << std::endl;
		return false;
	}



#if 0
	if (!LoadData())
	{
		return false;
	}
#endif
	//------------(o.luanda)-----------------

	return true;
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

void App::Update(float deltaTime)
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

#if 0
	camera.Update((float)glfwGetTime() * 0.05f, inputs);
	camera.Update(deltaTime, inputs);
#endif

	//push matrix/floats to shader
	glUseProgram(shader.shaderProgram);
	glUniform3f(glGetUniformLocation(shader.shaderProgram, "viewPos"), camera.from.x, camera.from.y, camera.from.z);

	glUniform1i(glGetUniformLocation(shader.shaderProgram, "nbrOfDir"), nbrOfDir);
	glUniform1i(glGetUniformLocation(shader.shaderProgram, "nbrOfPoint"), nbrOfPoint);

	glUniform1i(glGetUniformLocation(shader.shaderProgram, "nbrOfSpot"), nbrOfSpot);
	glUniform1i(glGetUniformLocation(shader.shaderProgram, "material.diffuse"), 0);

	glUniform1i(glGetUniformLocation(shader.shaderProgram, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(shader.shaderProgram, "material.shininess"), 128);

	for (int i = 0; i < lights.size(); i++)
	{
		lights[i]->Update(shader.shaderProgram);
	}

	glfwPollEvents();
	processInput(window);

}


void App::RunLoop()
{
	while (!glfwWindowShouldClose(window))
	{

		float cureentFrame = static_cast<float>(glfwGetTime());
		deltaTime = cureentFrame - lastFrame;
		lastFrame = cureentFrame;

		Update(deltaTime);

		Draw();

	}
}


void App::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.shaderProgram);

	Mat4 projView = camera.GetProjection() * camera.GetView();

	//(o.luanda): if the mesh is drawable opengl can draw it 
	for (int i = 0; i < meshes.size(); i++)
	{
		if (meshes[i]->model->modelDrawable)
		{
			meshes[i]->Draw(projView, shader.shaderProgram);
		}
		else if (meshes[i]->model->modelLoaded)
		{
			meshes[i]->InitTextureOpenGL();
			meshes[i]->model->InitOpenGl();
		}
	}
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
		if (!mouseCaptured)
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