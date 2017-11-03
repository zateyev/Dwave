#version 300 es
precision mediump int;
precision mediump float;

in vec4 backColor;

out vec4 fragColor;

void main(void)
{
    fragColor = backColor;
}
