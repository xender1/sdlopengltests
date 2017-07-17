#pragma once

#include <GL/glew.h>
#include <string>

namespace Shader
{

	class ShaderProgram 
	{
	public:
		ShaderProgram(const std::string& vertexShaderFile, const std::string&fragmentShaderFile);
		~ShaderProgram();

		void bind();
		void unbind();

	protected:
		void bindAttribute(GLuint location, const GLchar* name);

		virtual void bindAttributes() = 0;
		virtual void getUniformLocations() = 0;
	
	private:
		GLuint m_programId;

	};

}