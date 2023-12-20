#include "ShapeMaker.h"
#include "Vertex.h"
#define  NUM_ARRAY_ELEMENTS(a) (sizeof(a) / sizeof(*(a)))

ShapeData ShapeMaker::makeTriangle()
{
	ShapeData ret;

	Vertex vertices[] =
	{
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),

		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(vertices);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, vertices, sizeof(vertices));

	GLushort indices[] = {0, 1, 2};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));


	return ret;
}
