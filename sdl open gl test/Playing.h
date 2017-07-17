#pragma once

#include "GameState.h"

#include "Model.h"
#include "SimpleShader.h"
#include "BasicTexture.h"

namespace State 
{
	class Playing : public GameState
	{
	public:
		Playing(Application& application);

		void input() override;
		void update() override;
		void draw() override;

	private:
		Model m_model;

		Shader::SimpleShader m_shader;
		Texture::BasicTexture m_texture;
	};
}