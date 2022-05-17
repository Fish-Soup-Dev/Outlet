#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCords;

void main()
{
    gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_textue;

void main()
{
    vec4 texColor = texture(u_textue, texCords)
    color = u_color;
}