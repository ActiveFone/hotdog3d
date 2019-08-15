#include "TestBase.h"
#include <stb_image.h>

TestBase::TestBase()
{
	std::cout << "TestBase()" << std::endl;
}

TestBase::TestBase(const unsigned int width, const unsigned int height)
{

}

TestBase::~TestBase()
{
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void TestBase::processInput(GLFWwindow *window)
{

}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void TestBase::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void TestBase::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int TestBase::loadTexture()
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	const char* path = "res/img/container2.png";
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

bool TestBase::init()
{
	return true;
}

void TestBase::showTest(GLFWwindow *window)
{
	std::cout << "TestBase::showTest " << std::endl;
}