#version 300 es
precision mediump int;
precision mediump float;

in vec4 vertColor;

//
in vec3 position;
uniform mat4 MVP;

out vec4 backColor;
out vec4 pos;

void main(void)
{
    backColor = vertColor;

    // pos = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
    pos = MVP * vec4(position, 1.0);

    gl_Position = pos;
}
