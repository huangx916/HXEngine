#version 430 core

uniform sampler2D Layer1;
uniform sampler2D Layer2;
uniform sampler2D Layer3;
uniform sampler2D Layer4;
uniform sampler2D Control;

// fog
uniform int useFog;
uniform int fogType;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;

in vec4 vs_fs_diffuse_color;
in vec4 vs_fs_vertex_color;

in vec2 vs_fs_ControlTexcoord;
in vec4 vs_fs_Layer12Texcoord;
in vec4 vs_fs_Layer34Texcoord;

// fog
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
	
	if(useFog == 1)
	{
		// linear fog
		if(fogType == 0)
		{
			vec4 _fogColor = vec4(fogColor, 1.0);
			float fog  = (vs_fs_distance - fogStart)/fogEnd;
			fog = clamp(fog, 0.0, 1.0);
			fColor = mix(fColor, _fogColor, fog);
		}
	}	
}