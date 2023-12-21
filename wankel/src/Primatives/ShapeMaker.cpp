#include "ShapeMaker.h"
#include "Vertex.h"
#define  NUM_ARRAY_ELEMENTS(a) (sizeof(a) / sizeof(*(a)))

ShapeData ShapeMaker::makeTriangle()
{
	ShapeData ret;

	Vertex vertices[] =
	{

		glm::vec3(0.0f, 0.5f, 0.0f),
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

ShapeData ShapeMaker::makeCube()
{
	ShapeData ret;

	Vertex vertices[] = {
		// Front face
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), // bottom left
		glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), // bottom right
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), // top right
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), // top right
		glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), // top left
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), // bottom left

		// Right face
		glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f),

		// Back face
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

		// Left face
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

		// Top face
		glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f),

		// Bottom face
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f)
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(vertices);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, vertices, sizeof(vertices));

	GLushort indices[] = {
		// Front face
		0, 1, 2, // First triangle
		3, 4, 5, // Second triangle

		// Right face
		6, 7, 8, // First triangle
		9, 10, 11, // Second triangle

		// Back face
		12, 13, 14, // First triangle
		15, 16, 17, // Second triangle

		// Left face
		18, 19, 20, // First triangle
		21, 22, 23, // Second triangle

		// Top face
		24, 25, 26, // First triangle
		27, 28, 29, // Second triangle

		// Bottom face
		30, 31, 32, // First triangle
		33, 34, 35 // Second triangle
	};

	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));


	return ret;
}

ShapeData ShapeMaker::makeCube2()
{
	ShapeData ret;

	Vertex vertices[] = {
		// Define 8 unique vertices for the cube
		{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // 0 left-bottom-back
		{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // 1 right-bottom-back
		{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // 2 right-top-back
		{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f)}, // 3 left-top-back
		{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f)}, // 4 left-bottom-front
		{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)}, // 5 right-bottom-front
		{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // 6 right-top-front
		{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)} // 7 left-top-front
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(vertices);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, vertices, sizeof(vertices));

	GLushort indices[] = {
		// Front face
		4, 5, 6,
		6, 7, 4,

		// Back face
		1, 0, 3,
		3, 2, 1,

		// Left face
		0, 4, 7,
		7, 3, 0,

		// Right face
		5, 1, 2,
		2, 6, 5,

		// Top face
		3, 7, 6,
		6, 2, 3,

		// Bottom face
		0, 1, 5,
		5, 4, 0
	};

	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}
