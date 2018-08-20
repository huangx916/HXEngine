#version 330

uniform sampler2D MainTexture;
uniform vec4 DiffuseColor;

in vec2 vs_fs_texcoord;
out vec4 color;

void main(void)
{
	//vec4 fColor = texture(MainTexture, vs_fs_texcoord);
	vec4 fColor = DiffuseColor;
    color = fColor;
}
