#version 430 core

uniform sampler2D MainTexture;

in vec2 vs_fs_TexCoord;

out vec4 fColor;

void main()
{
	//fColor = vec4(0.2, 0.2, 0.2, 0.8);
	fColor = texture(MainTexture, vs_fs_TexCoord);
	//fColor = fColor * vec4(0.7,0.7,0.7,1);
}