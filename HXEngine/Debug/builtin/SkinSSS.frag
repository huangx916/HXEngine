#version 430

uniform sampler2D MainTexture;
uniform sampler2D NormalTex;
uniform sampler2D SmoothTex;
uniform sampler2D CurveTex;
uniform sampler2D SSSLUT;
uniform sampler2D KelemenLUT;

in vec4 vs_fs_texcoord;
out vec4 color;

void main(void)
{
	vec3 albedo = texture(MainTexture, vs_fs_texcoord.xy).rgb;
    color = vec4(albedo, 1);
}
