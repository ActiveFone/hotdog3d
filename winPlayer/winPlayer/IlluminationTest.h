#pragma once
#include "TestBase.h"

class IlluminationTest:public TestBase
{
public:
	IlluminationTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	IlluminationTest(const unsigned int width, const unsigned int height);
	~IlluminationTest();

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);

	void showTest(GLFWwindow *window);
private:

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
};