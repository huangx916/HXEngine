#version 430 core
#extension GL_NV_shadow_samplers_cube : enable

uniform samplerCube CubeMap;
in vec3 vs_fs_texcoord;
out vec4 fColor;

void main()
{
    vec4 fColor = vec4(1,1,1,1);
	//vec4 fColor = textureCube(CubeMap, vec3(1,1,1));
}