#pragma once
#include "TestBase.h"

class ModelLoadTest :public TestBase
{
public:
	ModelLoadTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	ModelLoadTest(const unsigned int width, const unsigned int height);
	~ModelLoadTest() {};

	void showTest(GLFWwindow *window);

private:
	unsigned int VAO, VBO;
};