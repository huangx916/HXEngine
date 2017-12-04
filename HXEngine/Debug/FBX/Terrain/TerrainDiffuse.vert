#version 430 core

uniform mat4 mvp_matrix;

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;

out vec2 vs_fs_texcoord;

void main()
{
	gl_Position = mvp_matrix * position;
	vs_fs_texcoord = texcoord;
}