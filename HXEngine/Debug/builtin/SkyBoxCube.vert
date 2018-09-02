#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

layout (location = 0) in vec3 position;
out vec3 vs_fs_texcoord;

void main()
{
	gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_texcoord = position;
}