#ifndef SHADER_H
#define SHADER_H

#include <string>

using namespace std;
class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;
	void setFloat4v(const string &name, float value1, float value2, float value3, float value4) const;
};

#endif
