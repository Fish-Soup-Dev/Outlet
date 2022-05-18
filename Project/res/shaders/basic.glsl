#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;

uniform mat4 u_MVP;
uniform float u_offset;

out vec4 v_pos;

float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

void main()
{
    vec4 nt = vec4(a_position.x, a_position.y + noise(vec2(a_position.x + u_offset, a_position.z + u_offset)) / 2, a_position.z, a_position.w);
    gl_Position = u_MVP * nt;
    v_pos = nt;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_pos;

void main()
{
    color = v_pos;
}