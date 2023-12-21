#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColour;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;
uniform vec3 dominatingColour;

out vec3 fragmentColour;

void main()
{

	vec4 v = vec4(position, 1.0);
	vec4 worldPosition = modelTransformMatrix * v;
    vec4 projectedPosition = projectionMatrix * worldPosition;
	gl_Position = projectedPosition;
	fragmentColour = vertexColour;

}

