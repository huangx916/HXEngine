#version 430 core

uniform sampler2D MainTexture;

// 线性雾
uniform int useFog;

in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;

// 线性雾
in float vs_fs_distance;

out vec4 fColor;

void main()
{
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	fColor = texture(MainTexture, vs_fs_texcoord) * vs_fs_diffuse_color;
	
	// 线性雾
	if(useFog == 1)
	{
		vec4 fogColor = vec4(0.5, 0.5, 0.5, 1.0);
		float fog  = (vs_fs_distance - 10)/30;
		fog = clamp(fog, 0.0, 1.0);
		pow(fog, 4);
		fColor = mix(fColor, fogColor, fog);
	}
}