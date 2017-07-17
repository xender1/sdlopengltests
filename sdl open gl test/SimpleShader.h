#pragma once
#include "ShaderProgram.h"

namespace Shader
{

	class SimpleShader : public ShaderProgram
	{
	public:
		SimpleShader();
		~SimpleShader();

	private:
		void bindAttributes() override;
		void getUniformLocations() override;

		GLuint m_locationTime = 0;
	};

}