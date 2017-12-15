#version 430 core

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;

in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;

out vec4 fColor;

void main()
{
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	fColor = texture(Texture1, vs_fs_texcoord);
}