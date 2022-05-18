#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;

uniform mat4 u_MVP;

out vec4 v_pos;

void main()
{
    gl_Position = u_MVP * a_position;
    v_pos = a_position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_pos;

void main()
{
    color = v_pos;
}