#pragma once

#include <GL\glew.h>
#include <vector>

class Model
{
public:
	Model(const std::vector<GLfloat>& vertexPositions);
	~Model();

	void bind();
	void unbind();

private:
	GLuint m_vertexId;

	//Graphics program
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

};

