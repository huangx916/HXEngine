#version 430 core

uniform sampler2D MainTexture;

in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;

out vec4 fColor;

void main()
{
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	fColor = texture(MainTexture, vs_fs_texcoord);// * vs_fs_diffuse_color;
}