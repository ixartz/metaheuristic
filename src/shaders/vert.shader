#version 150

in vec4 position;
in vec3 normal;
in vec4 color;

out vec3 normal_from_vshader;
out vec4 color_from_vshader;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * position;
	normal_from_vshader = normal;
	color_from_vshader = color;
}