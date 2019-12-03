#include "TestBase.h"

TestBase::TestBase()
{
	std::cout << "TestBase()" << std::endl;
}

TestBase::TestBase(const unsigned int width, const unsigned int height)
{
	nWidth = width;
	nHeight = height;

	// camera
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	lastX = nWidth / 2.0f;
	lastY = nHeight / 2.0f;
	firstMouse = true;

	// timing
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

TestBase::~TestBase()
{
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void TestBase::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void TestBase::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void TestBase::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
//unsigned int TestBase::loadTexture(const char* path)
//{
//	//return localLoadTexture(path);
//}

bool TestBase::init()
{
	return true;
}

void TestBase::showTest(GLFWwindow *window)
{
	std::cout << "TestBase::showTest " << std::endl;
}
