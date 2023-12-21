#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColour;

uniform mat4 modelTransformMatrix;
uniform mat4 rotationMatrix;
uniform mat4 projectionMatrix;
uniform vec3 dominatingColour;

out vec3 fragmentColour;

void main()
{

	vec4 v = vec4(position, 1.0);
	vec4 newRotation = rotationMatrix * v; 
	vec4 newPosition = modelTransformMatrix * newRotation;
	vec4 projectedPosition = projectionMatrix * newPosition;
	gl_Position =  projectedPosition;
	fragmentColour = vertexColour;

}

