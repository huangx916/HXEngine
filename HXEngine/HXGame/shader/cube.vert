#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;

out vec4 vs_fs_color;
out vec2 vs_fs_texcoord;

void main()
{
	// gl_Position = projection_matrix * view_matrix * model_matrix * position;
	gl_Position = mvp_matrix * position;
	// gl_Position = position * model_matrix * view_matrix * projection_matrix;
	
	// vs_fs_color = color;
	vs_fs_color = vec4(texcoord.x, texcoord.y, 1, 1);
	
	vs_fs_texcoord = texcoord;
}