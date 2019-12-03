#pragma once
#include "TestBase.h"

class GeometryTest :public TestBase
{
public:
	GeometryTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	GeometryTest(const unsigned int width, const unsigned int height);
	~GeometryTest() {};

	void showTest(GLFWwindow *window);

	void showModelTest(GLFWwindow *window);
private:
	unsigned int VAO, VBO;
};