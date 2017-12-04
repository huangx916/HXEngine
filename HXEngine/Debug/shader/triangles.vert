#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vUV;

out vec2 vs_fs_uv;

void main()
{
	gl_Position = vPosition;
	vs_fs_uv = vUV;
}