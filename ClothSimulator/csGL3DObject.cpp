
#include "csGL3DObject.h"

#include <wx\log.h>

void csGL3DObject::creategl(std::vector< Vertex* >& vertices, std::vector< unsigned int >& indices, GLenum usage)
{
	std::vector<glm::vec3> vertices_copy;
	for (Vertex* v: vertices)
		vertices_copy.push_back(glm::vec3(v->x, v->y, v->z));

	creategl(vertices_copy, indices, usage);
}

void csGL3DObject::creategl(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, GLenum usage)
{
	m_draw_count = indices.size();

	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	// generate 1 buffer
	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], usage);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Generate a buffer for the indices
	glGenBuffers(1, &m_elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void csGL3DObject::updategl(std::vector<Vertex*>& vertices)
{
	std::vector<glm::vec3> vertices_copy;
	for (Vertex* v : vertices)
		vertices_copy.push_back(glm::vec3(v->x, v->y, v->z));

	updategl(vertices_copy);
}

void csGL3DObject::updategl(std::vector<glm::vec3>& vertices)
{
	//wxLogDebug("count: %f", vertices[0].y);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void csGL3DObject::render()
{
	//glBindVertexArray(m_VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);

	//wxLogDebug("rendering %d, %d", m_draw_mode, m_draw_count);
	glDrawElements(
		m_draw_mode,      // mode
		m_draw_count,    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
}
