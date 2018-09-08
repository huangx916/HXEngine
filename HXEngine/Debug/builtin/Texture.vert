#version 330

uniform mat4 mvp_matrix;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;

out vec2 vs_fs_texcoord;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
}
