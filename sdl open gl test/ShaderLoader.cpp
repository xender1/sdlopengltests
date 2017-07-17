#include "ShaderLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Shader
{
	GLuint compileShader(const GLchar* source, GLenum type)
	{
		auto id = glCreateShader(type);

		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		GLchar infoLog[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			throw std::runtime_error("Error compiling shader: " + std::string(infoLog));
		}

		return id;
	}

	std::string getSource(const std::string sourceFile)
	{
		std::ifstream inFile(sourceFile + ".glsl");
		std::string source;
		std::stringstream stringStream;

		if (!inFile.is_open()) {
			throw std::runtime_error("Could not open file: " + sourceFile);
		}

		stringStream << inFile.rdbuf();
		source = stringStream.str();

		return source;
	}

	GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		auto id = glCreateProgram();

		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);

		glLinkProgram(id);

		//Check for errors
		GLint programSuccess = GL_TRUE;
		GLchar infoLog[512];
		glGetProgramiv(id, GL_LINK_STATUS, &programSuccess);
		if (programSuccess != GL_TRUE)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::runtime_error("Error linking program: " + std::string(infoLog));
		}

		return id;
	}

	GLuint loadShader(const std::string & vertexShaderFile, const std::string & fragmentShaderFile)
	{
		auto vertexSource = getSource(vertexShaderFile);
		auto fragmentSource = getSource(fragmentShaderFile);

		auto vertexShaderId = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
		auto fragmentShaderId = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

		auto programId = createProgram(vertexShaderId, fragmentShaderId);

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		return programId;
	}
}