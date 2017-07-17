#include "Playing.h"

std::vector<GLfloat> vertexPositions =
{ 
	0.5f, 0.5f,
	-0.5f, 0.5f,
	-0.5f, -0.5f,
	0.5f, -0.5f 
};

std::vector<GLfloat> textureCoords =
{
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0
};

std::vector<GLuint> indices = 
{
	0, 1, 2,
	2, 3, 0
};

namespace State
{
	Playing::Playing(Application& application)
		: GameState(application)
		, m_model(vertexPositions, textureCoords, indices)
	{
		m_texture.load("grass.png");
	}
	void Playing::input()
	{
	}
	void Playing::update()
	{
	}
	void Playing::draw()
	{
		m_shader.bind();
		m_model.bind();
		m_texture.bind();

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

		m_texture.unbind();
		m_model.unbind();
		m_shader.unbind();
	}
}