#version 430 core

uniform sampler2D tex;
uniform sampler2D tex2;

//in vec4 vs_fs_color;
in vec2 vs_fs_TexCoord;
in vec3 vs_fs_FontColor;

out vec4 fColor;

void main()
{
	//fColor = texture(tex, vs_fs_TexCoord);
	fColor = texture(tex2, vs_fs_TexCoord);
	fColor = vec4(vs_fs_FontColor.r, vs_fs_FontColor.g, vs_fs_FontColor.b, fColor.a);
	//fColor = vec4(0.0, 0.0, 1.0, 1.0);
	//fColor = vs_fs_color;
}