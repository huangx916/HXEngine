#version 330
//#include "_InverseMatrix.glsl"

uniform mat4 mvp_matrix;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;

out vec2 vs_fs_texcoord;

void main(void)
{
    //mat4 inverseMVP = inverse(mvp_matrix);
    //mat4 transposeMVP = transpose(mvp_matrix);
    gl_Position = mvp_matrix * position;
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
}
