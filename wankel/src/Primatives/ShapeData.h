#pragma once
#include <GL/glew.h>
#include "Vertex.h"

struct ShapeData
{
	ShapeData():
		vertices(0), numVertices(0),
		indices(0), numIndices(0)
	{
	}

	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	GLsizeiptr vertexBufferSize() const
	{
		return sizeof(Vertex) * numVertices;
	}

	GLsizeiptr indexBufferSize() const
	{
		return sizeof(GLushort) * numIndices;
	}

	void cleanup()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
	}
};
