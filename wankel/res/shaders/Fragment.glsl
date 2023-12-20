#version 430

out vec4 FragColor;
in vec3 fragmentColour;

void main()
{
	FragColor = vec4(fragmentColour, 1.0);
}