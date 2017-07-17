#include "ShaderProgram.h"
#include "ShaderLoader.h"
namespace Shader
{



	ShaderProgram::ShaderProgram(const std::string & vertexShaderFile, const std::string & fragmentShaderFile)
		: m_programId (loadShader(vertexShaderFile, fragmentShaderFile))
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_programId);
	}

	void ShaderProgram::bind()
	{
		glUseProgram(m_programId);
	}

	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgram::bindAttribute(GLuint location, const GLchar * name)
	{
		glBindAttribLocation(m_programId, location, name);
	}

}