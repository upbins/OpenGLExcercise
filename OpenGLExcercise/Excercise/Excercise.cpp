#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//矩阵相关用到头文件
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../opengl/src/Shader.h"
#include "../opengl/src/stb_image.h"
#include "../opengl//src/MyCamera.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixThird = 0.2f;
//定义camera一些属性
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.001f;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float firstMouse = true;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
float pitch = 0.0f; //俯仰角
float yaw = -90.0f;//偏航角
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("../shaders/shader_exercise.vs", "../shaders/shader_exercise.fs"); // you can name your shader files however you like

//float vertices[] = {
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
//float vertices[] = {
//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

//	-0.2f, -0.2f, -0.2f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
//	 0.2f, -0.2f, -0.2f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
//	 0.2f,  0.2f, -0.2f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//	 0.2f,  0.2f, -0.2f,    0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
//	-0.2f,  0.2f, -0.2f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
//	-0.2f, -0.2f, -0.2f,  	1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
// 
   //};
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  	1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};
	//顶点缓冲索引
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};
	glm::vec3 cubePositions[] = {
	  glm::vec3(0.5f,  0.5f,  0.0f),
	  glm::vec3(-0.5f, 0.5f, 0.0f),
	};
	unsigned int VAO, VBO, EBO;

	//初始化一些Gen
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//绑定
	glBindVertexArray(VAO);
	//绑定相关顶点缓冲数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////绑定索引缓冲对象
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	////生成纹理
	unsigned int texture1;
	int width, height, nrChannels;
	unsigned char *data;
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载资源
	data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Faild to load texture" << std::endl;
	}

	//释放纹理内存
	stbi_image_free(data);
	//第二张纹理贴图
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载资源
	data = stbi_load("../textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Faild to load texture" << std::endl;
	}
	ourShader.use();
	ourShader.setInt("outTexture", 0);
	ourShader.setInt("outTexture2", 1);
	ourShader.setFloat("mixThird", 0.2f);
	//测试一下矩阵
	//平移矩阵
	//glm::mat4 trans = glm::mat4(1.0);
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 1.0f)); 
	/*
		[1,0,0,10]	 [2]
		[0,1,0,10] * [2]
		[0,0,0, 0]   [1]
		[0,0,0, 1]	 [1]
	*/
	//glm::mat4 myMatrix = glm::translate(trans, cubePositions[1]); //组成一需要平移的矩阵
	//ourShader.setMat4("transform", myMatrix);
	/*
		[1,0,0,10]
		[0,1,0,10]
		[0,0,0, 0]
		[0,0,0, 1]
	*/
	//缩放矩阵,放在translate前后效果不一样,放前所有变量都变大,放后值变大translate前3个
	//glm::mat4 myScaleMatrix = glm::scale(myMatrix, glm::vec3(2.0f, 2.0f, 1.0f));

	////旋转矩阵
	//glm::mat4 myRotateMatrix = glm::rotate(myScaleMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f,1.0f));

	//glm::vec4 myVector(5.0f, 10.0f, 10.0f, 0.0f);//需要平移的大小 x,y,z,w
	//glm::vec4 transformedVector = myMatrix * myVector; // guess the result
	/*
		[1,0,0,10]	[5]
		[0,1,0,10] *[10]
		[0,0,0, 0]	[10]
		[0,0,0, 1]	[0]
	*/
	//transformedVector = myScaleMatrix * transformedVector;
	//transformedVector = myRotateMatrix * transformedVector;
	//std::cout << "Faild to load texture1" << transformedVector.x<< transformedVector.y<< transformedVector.z<< std::endl;
	//ourShader.setMat4("transform", myRotateMatrix);

	//camera
	//创建一个model矩阵
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//创建一个view矩阵
	glm::mat4 view = glm::mat4(1.0f);
	// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
	view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);//glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//创建一个project矩阵
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
	ourShader.setMat4("model", model);
	ourShader.setMat4("view", view);
	ourShader.setMat4("projection", projection);
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		ourShader.setFloat("mixThird", mixThird);
		ourShader.use();


		//位移的测试代码
		//for (int i = 0; i < 2; i++)
		//{
		//	glm::mat4 trans = glm::mat4(1.0);
		//	trans = glm::translate(trans, cubePositions[i]); //组成一需要平移的矩阵
		//	float angle = 20.0f * i;
		//	trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.5f));
		//	ourShader.setMat4("transform", trans);
		//	glDrawArrays(GL_TRIANGLES, i * 6, 6 + i*6);
		//};
		//glDrawArrays(GL_TRIANGLES, 0, 6);
	/*	glm::mat4 myScaleMatrix = glm::scale(myMatrix, glm::vec3(float(glfwGetTime())*0.1, float(glfwGetTime())*0.1f, 1.0f));
		glm::mat4 myRotateMatrix = glm::rotate(myScaleMatrix, float(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.setMat4("transform", myRotateMatrix);*/
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//自动旋转三角形
		/*glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model,float(glfwGetTime()), glm::vec3(0.5f, 0.5f, 0.5f));
		ourShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);*/
		glm::mat4 view = glm::mat4(1.0f);
		// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		ourShader.setMat4("model", view);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixThird += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixThird >= 1.0f)
			mixThird = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixThird -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixThird <= 0.0f)
			mixThird = 0.0f;
	}
	cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
