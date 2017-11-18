#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 vs_fs_color;

void main()
{
	gl_Position = vPosition;
	vs_fs_color = vColor;
}