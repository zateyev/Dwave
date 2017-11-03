#version 300 es
precision mediump int;
precision mediump float;

in vec4 vertColor;

in vec3 position; // VerPos
uniform mat4 MVP;

out vec4 frontColor;
out vec4 pos;

void main(void)
{
    frontColor = vertColor;

    pos = MVP * vec4(position, 1.0);
    gl_Position = pos;
}
