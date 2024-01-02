#version 430 core

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColour;

uniform mat4 fullTransformMatrix;
uniform vec3 dominatingColour;

out vec3 fragmentColour;

void main()
{

	vec4 v = vec4(position, 1.0);
	gl_Position =  fullTransformMatrix * v;
	fragmentColour = vertexColour;

}

