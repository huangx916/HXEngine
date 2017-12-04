#version 430 core

uniform sampler2D MainTexture;

in vec2 vs_fs_uv;
out vec4 fColor;

void main()
{
	//fColor = vec4(0.0, 0.0, 1.0, 1.0);
	//fColor = vs_fs_color;
	fColor = texture(MainTexture, vs_fs_uv);
	//fColor = vec4(vs_fs_uv.x, vs_fs_uv.y, 0, 1);
}