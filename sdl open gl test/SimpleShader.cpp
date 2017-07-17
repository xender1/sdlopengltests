#include "SimpleShader.h"

Shader::SimpleShader::SimpleShader()
	: ShaderProgram("Simple_Vertex", "Simple_Fragment")
{
	bindAttributes();
}

Shader::SimpleShader::~SimpleShader()
{
}

void Shader::SimpleShader::bindAttributes()
{
	bindAttribute(0, "inVertexPosition");
}

void Shader::SimpleShader::getUniformLocations()
{
}
