#version 150

in vec4 color_from_vshader;
in vec3 normal_from_vshader;
out vec4 out_color;

void main()
{
	vec4 ambient = color_from_vshader * vec4(0.3, 0.3, 0.3, 1.0);

	float theta = clamp(dot(normal_from_vshader, vec3(0.0, 0.0, -1.0)), 0, 1);
	vec4 diffuse = color_from_vshader * vec4(1.0, 1.0, 1.0, 1.0) * theta;

	out_color = ambient + diffuse;
}