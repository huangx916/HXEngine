#version 330

uniform sampler2D MainTexture;
uniform vec4 DiffuseColor;

uniform vec4 Albedo;
uniform vec4 Specular;
uniform float Smoothness;

in vec2 vs_fs_texcoord;
out vec4 color;

void main(void)
{
	vec4 fColor = texture(MainTexture, vs_fs_texcoord);
	//vec4 fColor = DiffuseColor;
	//vec4 fColor = texture(MainTexture, vs_fs_texcoord) * DiffuseColor;
    color = fColor;
}
