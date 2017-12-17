#version 430 core

uniform sampler2D Layer1;
uniform sampler2D Layer2;
uniform sampler2D Layer3;
uniform sampler2D Layer4;
uniform sampler2D Control;

// 线性雾
uniform int useFog;

in vec4 vs_fs_diffuse_color;
in vec4 vs_fs_vertex_color;

in vec2 vs_fs_ControlTexcoord;
in vec4 vs_fs_Layer12Texcoord;
in vec4 vs_fs_Layer34Texcoord;

// 线性雾
in float vs_fs_distance;

out vec4 fColor;

void main()
{
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	//fColor = texture(MainTexture, vs_fs_texcoord) * vs_fs_vertex_color * vs_fs_diffuse_color;
	vec4 controlColor = texture(Control, vs_fs_ControlTexcoord);
	fColor = controlColor.r * texture(Layer1, vs_fs_Layer12Texcoord.xy);
	fColor += controlColor.g * texture(Layer2, vs_fs_Layer12Texcoord.zw);
	fColor += controlColor.b * texture(Layer3, vs_fs_Layer34Texcoord.xy);
	fColor += controlColor.a * texture(Layer4, vs_fs_Layer34Texcoord.zw);
	
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