#version 330 core

layout (location = 0) in vec2 position;
layout (location = 3) in vec3 in_color;

out vec3 out_color;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
	out_color = in_color;
}