#version 300 es

in vec3 position;
in vec4 vertColor;
out vec3 worldSpaceCoords;
out vec4 projectedCoords;

uniform mat4 MVP;

void main()
{
	worldSpaceCoords = vertColor.xyz;
	gl_Position = MVP * vec4(position, 1.0);
	projectedCoords =  gl_Position;
}
