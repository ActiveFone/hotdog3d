#pragma once
#include "TestBase.h"

class InstancingTest :public TestBase
{
public:
	InstancingTest() {
		std::cout << "IlluminationTest.ctor()" << std::endl;
	};
	InstancingTest(const unsigned int width, const unsigned int height);
	~InstancingTest() {};

	void showTest(GLFWwindow *window);
	void showRockTest(GLFWwindow *window);
private:

};