#version 330

//uniform sampler2D MainTexture;
uniform samplerCube CubeMap;

//in vec2 vs_fs_texcoord;
in vec3 reflectvec;
out vec4 color;

void main(void)
{
	//vec4 fColor = texture(MainTexture, vs_fs_texcoord);
    //vec4 fColor = textureCube(CubeMap, vec3(1,1,1));
	//vec4 fColor = vec4(reflectvec, 1);
	vec4 fColor = textureCube(CubeMap, reflectvec.stp);
    color = fColor;
}
