#version 430 core
#extension GL_NV_shadow_samplers_cube : enable

uniform samplerCube CubeMap;
in vec3 vs_fs_texcoord;
out vec4 fColor;

void main()
{
    //fColor = vec4(1,1,1,1);
	fColor = textureCube(CubeMap, -vs_fs_texcoord);
}