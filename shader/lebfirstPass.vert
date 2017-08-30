#version 300 es

in vec3 position;
out vec3 worldSpaceCoords;

uniform mat4 MVP;

void main()
{
	worldSpaceCoords = position + vec3(0.5, 0.5, 0.5); //move it from [-0.5;0.5] to [0,1]
	gl_Position = MVP * vec4(position, 1.0);
}
