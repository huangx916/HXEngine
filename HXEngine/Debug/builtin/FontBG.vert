#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
uniform mat4 mvp_matrix;

out vec2 vs_fs_TexCoord;

void main()
{
	gl_Position = mvp_matrix * vPosition;
	vs_fs_TexCoord = vTexCoord;
}