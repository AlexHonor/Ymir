#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 color;

uniform mat4 MVP;
out vec3 out_color;
out vec3 out_normal;

void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
	out_color = color;
}