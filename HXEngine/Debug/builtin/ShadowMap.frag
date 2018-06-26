#version 330

uniform sampler2D MainTexture;

in vec2 vs_fs_texcoord;
out vec4 color;

void main(void)
{
	vec4 fColor = texture(MainTexture, vs_fs_texcoord);
	if(fColor.a < 0.5f)
	{
		discard;
	}
    color = vec4(1.0);
}
