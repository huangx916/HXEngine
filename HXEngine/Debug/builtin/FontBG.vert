#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
uniform mat4 mvp_matrix;

out vec2 vs_fs_TexCoord;

void main()
{
	gl_Position = mvp_matrix * vec4(vPosition, 1);
	vs_fs_TexCoord = vTexCoord;
}