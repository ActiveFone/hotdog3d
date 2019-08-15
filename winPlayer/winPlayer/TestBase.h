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

class TestBase
{
public:
	TestBase();
	TestBase(const unsigned int width, const unsigned int height);
	~TestBase();

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);
	unsigned int loadTexture();

	void showTest(GLFWwindow *window);

	unsigned int nWidth;
	unsigned int nHeight;

	GLFWwindow* mWindow;

private:

	bool init();
};