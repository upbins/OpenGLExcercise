#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../opengl/src/stb_image.h"
//#include "../opengl/src/MyShader.h"
#include "../opengl/src/MyCamera.h"
#include "Material.h"
#include "../opengl/src/Shader.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include <iostream>
using namespace glm;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int LoadImage(const GLchar* _imageName, const GLint internaleFormat,const GLenum format,int textureSlot);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MyCamera MyCameraClass(vec3(0.0f, 0.0f,3.0f),glm::radians(0.0f),glm::radians(180.0f),glm::vec3(0,1.0f,0));

//平行光
//LightDirectional light =  LightDirectional(glm::vec3(10.0f,10.0f,-5.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0.0f),glm::vec3(10.0f,10.0f,10.0f));

//点光源
//LightPoint light =  LightPoint(glm::vec3(1.0f,1.0f,-1.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0f),0.0f),glm::vec3(10.0f,10.0f,10.0f));

//聚光灯
LightSpot light =  LightSpot(glm::vec3(0.0f,5.0f,0.0f),glm::vec3(glm::radians(90.0f),0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));

float lastX;
float lastY;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float vertices[] = {
		//pos					//texture 		//normal			
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 	0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 	0.0f,  0.0f, -1.0f, 
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,  0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 	0.0f,  0.0f, -1.0f, 

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f,		0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,		0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,   	0.0f, 1.0f,		1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f,		1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,		1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,		0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,		0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,		0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  	0.0f, 1.0f,		0.0f,  1.0f,  0.0f,
};

glm::vec3 cubePositions[] = 
{
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.001f;
float fov = 45.0f;
float yoffset = -0.001f;
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	Shader* ourShader = new Shader("../shaders/lighting_map.vs", "../shaders/lighting_map.fs"); // you can name your shader files however you like
	Shader* lampShader = new Shader("../shaders/shader_original_light.vs", "../shaders/shader_original_light.fs"); 
	Material* myMaterial = new Material(
		ourShader,
		LoadImage("../textures/container2.png",GL_RGBA,GL_RGBA,Shader::DIFFUSE), //glm::vec3(1.0f,1.0f,1.0f),
		glm::vec3(1.0f,1.0f,1.0f),
		LoadImage("../textures/container2_specular.png",GL_RGBA,GL_RGBA,Shader::SPECULAR),//		glm::vec3(1.0f,1.0f,1.0f),
		64.0f);

	unsigned int VAO, VBO;

	//初始化一些Gen
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//绑定
	glBindVertexArray(VAO);
	//绑定相关顶点缓冲数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//纹理属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//lightmap texture
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
	
	unsigned int textureEmission;
	textureEmission = LoadImage("../textures/matrix.jpg",GL_RGB,GL_RGB,Shader::EMISSION);
	// unsigned int texture2;
	// texture2 = LoadImage("../textures/awesomeface.png",GL_RGB,GL_RGBA,1);
	// ourShader->use();
	// ourShader->setInt("texture1",0);
	// ourShader->setInt("texture2",1);

	//创建光源点坐标
	unsigned int CubeVAO;
	//初始化一些Gen
	glGenVertexArrays(1, &CubeVAO);
	//绑定
	glBindVertexArray(CubeVAO);
	
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//绑定相关顶点缓冲数据
	// //camera
	//创建一个model矩阵
	// glm::mat4 model = glm::mat4(1.0f);
	// model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//创建一个view矩阵
	// glm::mat4 view = glm::mat4(1.0f);
	// // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	// view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);//glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//创建一个project矩阵
	// glm::mat4 projection = glm::mat4(1.0f);
	// projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
	//ourShader.setMat4("model", model);
	//ourShader.setMat4("view", view);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,myMaterial->diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D,textureEmission);
		// render
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 viewMat =  glm::mat4(1.0);
			// glm::mat4 proMat =  glm::mat4(1.0);
			glm::mat4 modelMat = glm::mat4(1.0);
			modelMat = glm::translate(modelMat, cubePositions[i]);
			viewMat = MyCameraClass.GetViewMatrix();
			//float angle = 5.0f * i;
			//modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(MyCameraClass.Zoom), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
			ourShader->use();
			ourShader->setMat4("model", modelMat);
			ourShader->setMat4("view", viewMat);
			ourShader->setMat4("projection", projection);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// glm::vec3 lightColor;
			// lightColor.x = sin(glfwGetTime() * 2.0f);
			// lightColor.y = sin(glfwGetTime() * 0.7f);
			// lightColor.z = sin(glfwGetTime() * 1.3f);
			// glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
			// glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响
			ourShader->setVec3("cameraPos",MyCameraClass.Position.x,MyCameraClass.Position.y,MyCameraClass.Position.z);
			ourShader->setVec3("light.objectColor", 1.0f,1.0f,1.0f);
			ourShader->setVec3("light.ambientColor",0.2f,0.2f,0.2f);
			//漫反射光受光源颜色影响,计算的时候可以直接套用光源颜色
			//ourShader->setVec3("light.diffuseColor",light.color.x,light.color.y,light.color.z);
			//ourShader->setVec3("light.ambientColor",ambientColor);
			//ourShader->setVec3("light.diffuseColor",diffuseColor);
			ourShader->setVec3("light.lightColor",light.color.x,light.color.y,light.color.z);
			ourShader->setVec3("light.lightPos",light.position.x,light.position.y,light.position.z);
			//平行光源测试
			//ourShader->setVec3("light.lightDirection",light.direction);
			//material set
			ourShader->setVec3("material.ambient",myMaterial->ambient);
			//ourShader->setVec3("material.diffuse",myMaterial->diffuse);
			ourShader->setInt("material.diffuse",Shader::DIFFUSE);
			ourShader->setInt("material.specular",Shader::SPECULAR);
			//ourShader->setInt("material.emission",Shader::EMISSION);
			//ourShader->setVec3("material.specular",myMaterial->specular);
			ourShader->setFloat("material.shininess",myMaterial->shininess);

			//attenuation set 
			// ourShader->setFloat("attenuation.constant",light.constant);
			// ourShader->setFloat("attenuation.linear",light.linear);
			// ourShader->setFloat("attenuation.quadratic",light.quadratic);

			// //SpotLight
			ourShader->setFloat("lightSpot.cosInnerPhy",light.cosInnerPhy);
			ourShader->setFloat("lightSpot.cosOutterPhy",light.cosOutterPhy);
			ourShader->setVec3("lightSpot.spotDirection",light.direction);
			// ourShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
			// ourShader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		}
		glm::mat4 lampviewMat =  glm::mat4(1.0);
		lampviewMat = MyCameraClass.GetViewMatrix();
		glm::mat4 lampmodelMat = glm::mat4(1.0);
		lampmodelMat = glm::translate(lampmodelMat,light.position);
		lampmodelMat = glm::scale(lampmodelMat,glm::vec3(0.2));
		glm::mat4 lampprojection = glm::mat4(1.0f);
		lampprojection = glm::perspective(glm::radians(MyCameraClass.Zoom), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		lampShader->use();
		lampShader->setMat4("model", lampmodelMat);
		lampShader->setMat4("view", lampviewMat);
		lampShader->setMat4("projection", lampprojection);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(CubeVAO);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		MyCameraClass.UpdateCameraPos();
	}

	glfwTerminate();
	return 0;
}

unsigned int LoadImage(const GLchar* _imageName,const GLint internaleFormat,const GLenum format,int textureSlot)
{
	////生成纹理
	unsigned int texture;
	int width, height, nrChannels;
	unsigned char *data;
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载资源
	data = stbi_load(_imageName, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internaleFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Faild to load texture" << std::endl;
	}
	//释放纹理内存
	stbi_image_free(data);
	return texture;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MyCameraClass.SpeedZ = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MyCameraClass.SpeedZ = -1.0f;
	else
		MyCameraClass.SpeedZ = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MyCameraClass.SpeedX = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MyCameraClass.SpeedX = -1.0f;
	else
		MyCameraClass.SpeedX = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		MyCameraClass.SpeedY = -1.0f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		MyCameraClass.SpeedY = 1.0f;
	else
		MyCameraClass.SpeedY = 0.0f;

	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	// 	MyCameraClass.ProcessKeyboard(MOVEFORWARD, deltaTime);
	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	// 	MyCameraClass.ProcessKeyboard(MOVEBACKWARD, deltaTime);
	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	// 	MyCameraClass.ProcessKeyboard(MOVELEFT, deltaTime);
	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	// 	MyCameraClass.ProcessKeyboard(MOVERIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	
	MyCameraClass.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//MyCameraClass.ProcessMouseScroll(yoffset);
}