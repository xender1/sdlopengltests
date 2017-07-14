#include "Playing.h"

namespace State
{
	Playing::Playing(Application& application)
		: GameState(application)
		, m_model({0.3f, 0.3f,
				  -0.3f, 0.3f,
				  -0.3f, -0.3f,
				  -0.3f, -0.3f,
				   0.3f, -0.3f,
				   0.3f, 0.3f})
	{
	}
	void Playing::input()
	{
	}
	void Playing::update()
	{
	}
	void Playing::draw()
	{
		m_model.bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		m_model.unbind();
	}
}