#version 330
//#include "_InverseMatrix.glsl"

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

out vec2 vs_fs_texcoord;
out vec3 vs_fs_normal;
out vec3 vs_fs_position;

void main(void)
{
    //mat4 inverseMVP = inverse(mvp_matrix);
    //mat4 transposeMVP = transpose(mvp_matrix);
    gl_Position = mvp_matrix * vec4(position,1);
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	vs_fs_normal = (model_matrix * vec4(normal,0)).xyz;
    vs_fs_position = (model_matrix * vec4(position,1)).xyz;
}
