#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_pos;

void main()
{
    color = vec4(0.0f, 0.0f, v_pos.y * 2.0f + 0.2f, 1.0f);
}