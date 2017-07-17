#pragma once

#include <GL\glew.h>
#include <vector>

class Model
{
public:
	Model(const std::vector<GLfloat>& vertexPositions,
		const std::vector<GLfloat>& textureCoordinates,
		const std::vector<GLuint>& indeces);
	~Model();

	void bind();
	void unbind();

	GLuint getIndicesCount() const;

private:
	void addVBO(int dim, const std::vector<GLfloat>& data);
	void addEBO(const std::vector<GLuint>& indices);

	std::vector<GLuint> m_buffers;
	GLuint m_vboCount = 0;
	GLuint m_indicesCount = 0;

	GLuint m_vao = 0;

};

