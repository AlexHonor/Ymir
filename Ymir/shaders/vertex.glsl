#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 MVP;
out vec3 out_color;
out vec3 out_normal;

void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
	out_color = color;
}