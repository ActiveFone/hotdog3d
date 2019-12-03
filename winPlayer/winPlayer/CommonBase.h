#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stbImg/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class CommonBase
{
public:
	//CommonBase() {};
	//~CommonBase();

	unsigned int loadTexture(const char* path);
	
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);
};