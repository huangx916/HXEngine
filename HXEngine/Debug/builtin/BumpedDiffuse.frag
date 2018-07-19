#version 430 core

uniform sampler2D MainTexture;
uniform sampler2D NormalMap;
in vec4 vs_fs_texcoord;

in vec4 vs_fs_normal;
in vec3 vs_fs_light_dir;
out vec4 fColor;


void main()
{
	fColor = texture(MainTexture, vs_fs_texcoord.xy);
	
	vec3 normal = 2.0 * texture(NormalMap, vs_fs_texcoord.zw).rgb - 1.0;
	normal = normalize(normal);
	float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
	
	//vec3 lightDir = vec3(-1,1,1);
	//vec3 normal = normalize(vs_fs_normal.xyz);
	//float diffuse = max(0.0, dot(normal, lightDir));
	
	vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
	fColor = vec4(rgb, fColor.a);
	
}