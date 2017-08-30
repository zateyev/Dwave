#version 300 es

precision mediump float;

in vec3 worldSpaceCoords;
out vec4 fragColor;

void main()
{
	fragColor = vec4( worldSpaceCoords.x , worldSpaceCoords.y, worldSpaceCoords.z, 1 );
}
