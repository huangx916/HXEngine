#version 330

uniform mat4 model_view_projection_matrix;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;

out vec2 vs_fs_texcoord;

void main(void)
{
    gl_Position = model_view_projection_matrix * position;
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
}
