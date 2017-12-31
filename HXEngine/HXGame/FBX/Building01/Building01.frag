#version 430 core

uniform sampler2D MainTexture;

// fog
uniform int useFog;
uniform int fogType;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;

// 光照 世界空间
uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 eyePos;

in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;

// fog
in float vs_fs_distance;

// 光照 世界空间
in vec4 vs_fs_normal;
in vec4 vs_fs_position;

out vec4 fColor;

void main()
{
	fColor = texture(MainTexture, vs_fs_texcoord) * vs_fs_diffuse_color;
	
	// 光照处理 世界坐标系下
	vec3 eyeDir = eyePos - vs_fs_position.xyz;
	//float diffuse = max(0.0, dot(normalize(vs_fs_normal.xyz), normalize(-lightDir)));
	//vec3 scatteredLight = ambient + lightColor *diffuse;
	//vec3 rgb = fColor.rgb * scatteredLight;
	//fColor = vec4(rgb, fColor.a);
	float diffuse = max(0.0, dot(normalize(vs_fs_normal.xyz), normalize(vec3(1,1,1))));
	vec3 scatteredLight = min(ambient + vec3(1,1,1) *diffuse, vec3(1.0));
	vec3 rgb = fColor.rgb * scatteredLight;
	fColor = vec4(rgb, fColor.a);
	
	// 线性雾
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
	
	//fColor = vec4(vs_fs_normal.xyz, 1);
}