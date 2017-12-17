#version 430 core

in vec4 vs_fs_color;

out vec4 fColor;

void main()
{
	// fColor = vec4(0.0, 1.0, 0.0, 1.0);
	fColor = vs_fs_color;
}