// HotDog3D.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <GL2017/stb_image.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
#include "glShader.h"

#pragma comment(lib, "glfw3.lib")

using namespace std;

float verticesWithCoods[] = {
	// ---- pos ----     ----color-----		--- texture ---
	0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,   0.0f, 0.5f, 1.0f,    0.0f, 1.0f,
};

float vertices[] = {
	// ---- pos ----     ----color-----		
	0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f,   0.0f, 0.5f, 1.0f,
};

float cumbVertices[] = {
	// ---- pos ----     
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
};

unsigned int indices[] = {
	0,1,3,
	1,2,3
};

float texCoods[] = {
	0.0f, 0.0f, // 左下角
	1.0f, 0.0f, // 右下角
	1.0f, 1.0f, // 右上角
	0.0f, 1.0f, // 左上角
};

int WIDTH = 800;
int HEIGHT = 600;

unsigned int VAO, VBO, EBO, Texture1, Texture2;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float pitch = 0.0f;
float yaw = 0.0f;

float lastX = 400, lastY = 300;
bool firstMouse = true;
float fov = 45.0f;

GLFWwindow* initWindow();
void buildBuffers();
void setAttribs();
void doLoop(GLFWwindow* wd, Shader sd);
void releaseBuffers();
void buildTexture();
void useShader();
void setShaderUniformEveryLoop(Shader sd);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void pitchRotate(glm::vec3 initFront, float pitch);
void yawRotate(glm::vec3 initFront, float yaw);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "lernOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
};

void buildBuffers() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cumbVertices), cumbVertices, GL_STATIC_DRAW);
}

void setAttribs() {
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 颜色属性
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void buildTexture() {
	glGenTextures(1, &Texture1);
	glBindTexture(GL_TEXTURE_2D, Texture1);

	//环绕 过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载 生成纹理
	int width, height, nrChannels;
	unsigned char *imgData = stbi_load("img/container.jpg", &width, &height, &nrChannels, 0);

	if (imgData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Faild to load texture!" << std::endl;
	}
	stbi_image_free(imgData);

	glGenTextures(1, &Texture2);
	glBindTexture(GL_TEXTURE_2D, Texture2);

	//环绕 过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load("img/smile.png", &width, &height, &nrChannels, 0);

	if (imgData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Faild to load texture!" << std::endl;
	}

	stbi_image_free(imgData);
}

void doLoop(GLFWwindow* window, Shader ourShader) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture2);

	setShaderUniformEveryLoop(ourShader);

	//ourShader.use();
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void releaseBuffers() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}

void useShader() {
	Shader ourShader("shader/shader.vs", "shader/shader.fs");
	ourShader.use();
	ourShader.setInt("uniTexture1", 0);
	ourShader.setInt("uniTexture2", 1);
}

void setShaderUniformEveryLoop(Shader ourShader) {
	glm::mat4 modelTrans = glm::mat4(1.0f);
	modelTrans = glm::rotate(modelTrans, glm::radians(60.0f), glm::vec3(1.0f, 0.5f, 0.0f));

	/*float radius = 10.0f;
	float camX = sin(2 * glfwGetTime()) * radius;
	float camZ = cos(3 * glfwGetTime()) * radius;*/

	glm::mat4 viewTrans = glm::mat4(1.0f);
	//viewTrans = glm::translate(viewTrans, glm::vec3(0.0f, 0.0f, -3.0f));
	//viewTrans = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	viewTrans = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUP);

	glm::mat4 projectTrans = glm::mat4(1.0f);
	projectTrans = glm::perspective(glm::radians(fov), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);

	glm::mat4 mvpTrans = glm::mat4(1.0f);
	mvpTrans = projectTrans * viewTrans * modelTrans;
	glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "mvp"), 1, GL_FALSE, glm::value_ptr(mvpTrans));
}

void processInput(GLFWwindow *window) {

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	float deltaAngle = 10.01f;
	float fPitch = 0.0f;
	float fYaw = 0.0f;
	glm::vec3 initFront = glm::vec3(0.0f, 0.0f, -1.0f);

	std::cout << "get time every loop: " << deltaTime << std::endl;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUP)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUP)) * cameraSpeed;

	/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	pitch = (pitch + deltaAngle) > 19.0f ? 19.0f : (pitch + deltaAngle);
	fPitch = fPitch + deltaAngle;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	pitch = (pitch - deltaAngle) < -19.0f ? -19.0f : (pitch - deltaAngle);
	fPitch = fPitch - deltaAngle;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	yaw = (yaw + deltaAngle) > 19.0f ? 19.0f : (yaw + deltaAngle);
	fYaw = fYaw + deltaAngle;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	yaw = (yaw - deltaAngle) < -19.0f ? -19.0f : (yaw - deltaAngle);
	fYaw = fYaw - deltaAngle;*/

	/*pitchRotate(initFront, fPitch);
	yawRotate(initFront, fYaw);*/
	//glm::vec3 front;
	/*front.z = -cos(glm::radians(fPitch)) * cos(glm::radians(fYaw));
	front.y = sin(glm::radians(fPitch));
	front.x = cos(glm::radians(fPitch)) * sin(glm::radians(fYaw));
	cameraFront = glm::normalize(front);*/
}

void pitchRotate(glm::vec3 initFront, float pitch) {

	float rPitch = glm::radians(pitch);
	glm::mat3 pitchMat = glm::mat3(1.0f, 0.0f, 0.0f,
		0.0f, cos(rPitch), -sin(rPitch),
		0.0f, sin(rPitch), cos(rPitch));
	cameraFront = pitchMat * cameraFront;
}

void yawRotate(glm::vec3 initFront, float yaw) {

	float rYaw = glm::radians(yaw);
	glm::mat3 yawMat = glm::mat3(cos(rYaw), 0.0f, sin(rYaw),
		0.0f, 1.0f, 0.0f,
		-sin(rYaw), 0.0f, cos(rYaw));
	cameraFront = yawMat * cameraFront;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;

	if (fov >= 45.0f)
		fov = 45.0f;
}

int main(int argc, char** argv)
{
	GLFWwindow* mWindow = initWindow();

	//glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	buildBuffers();

	buildTexture();

	setAttribs();

	glEnable(GL_DEPTH_TEST);

	//useShader();

	Shader ourShader("shader/shader.vs", "shader/shader.fs");
	ourShader.use();
	ourShader.setInt("uniTexture1", 0);
	ourShader.setInt("uniTexture2", 1);
	glfwSetCursorPosCallback(mWindow, mouse_callback);
	glfwSetScrollCallback(mWindow, scroll_callback);

	while (!glfwWindowShouldClose(mWindow))
	{
		processInput(mWindow);

		doLoop(mWindow, ourShader);
	}

	releaseBuffers();

	glfwTerminate();

	//system("pause");
	return 0;
}
