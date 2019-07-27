#pragma once
#include <camera.h>
#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_m.h>

#include <iostream>

class IlluminationTest
{
public:
	IlluminationTest();
	IlluminationTest(const unsigned int width, const unsigned int height);
	~IlluminationTest();

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);
	unsigned int loadTexture();

	void showTest(GLFWwindow *window);
private:
	unsigned int nWidth;
	unsigned int nHeight;

	GLFWwindow* mWindow;

	// camera
	Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;

	// timing
	float deltaTime;
	float lastFrame;

	// lighting
	glm::vec3 lightPos;

	bool init();
};