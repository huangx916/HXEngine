#version 430 core

uniform sampler2D MainTexture;
uniform sampler2D NormalMap;
uniform sampler2D MainTexture2;
uniform sampler2D NormalMap2;
in vec4 vs_fs_texcoord;
in vec4 vs_fs_detailtexcoord;

in vec4 vs_fs_normal;
in vec3 vs_fs_light_dir;
out vec4 fColor;


void main()
{
	// 顶点法线
	//fColor = texture(MainTexture, vs_fs_texcoord.xy);
	//vec3 lightDir = normalize(vec3(-1,1,1));
	//vec3 normal = normalize(vs_fs_normal.xyz);
	//float diffuse = max(0.0, dot(normal, lightDir));
	//vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
	//fColor = vec4(rgb, fColor.a);
	
	// 法线贴图
	//fColor = texture(MainTexture, vs_fs_texcoord.xy);
	//vec3 normal = 2.0 * texture(NormalMap, vs_fs_texcoord.zw).rgb - 1.0;
	//normal = normalize(normal);
	//float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
	//vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
	//fColor = vec4(rgb, fColor.a);
	
	// 细节法线贴图
	float _Opacity = 1.0;
	vec4 _Color = vec4(1,1,1,1);
	vec4 tex = texture(MainTexture, vs_fs_texcoord.xy);
	vec4 tex2 = texture(MainTexture2, vs_fs_detailtexcoord.xy);
	vec4 dest;
	_Opacity*=tex.a;
	bvec3 tmpvar = lessThanEqual(tex2.rgb, vec3(0.5,0.5,0.5));
	if(tmpvar.x)
	{
		dest.r = 2*tex.r*tex2.r;
	}
	else
	{
		dest.r = 1-2*(1-tex.r)*(1-tex2.r);
	}
	if(tmpvar.y)
	{
		dest.g = 2*tex.g*tex2.g;
	}
	else
	{
		dest.g = 1-2*(1-tex.g)*(1-tex2.g);
	}
	if(tmpvar.z)
	{
		dest.b = 2*tex.b*tex2.b;
	}
	else
	{
		dest.b = 1-2*(1-tex.b)*(1-tex2.b);
	}
	dest.rgb = tex2.rgb + _Opacity*(dest.rgb-tex2.rgb);
	dest.rgb *= _Color.rgb;
	fColor.rgb = dest.rgb;
	fColor.a = tex2.a * _Color.a;
	vec4 norm = texture(NormalMap, vs_fs_texcoord.zw);
	vec4 norm2 = texture(NormalMap2, vs_fs_detailtexcoord.zw);
	bvec4 tmpvar_2 = lessThanEqual(norm2, vec4(0.5,0.5,0.5,0.5));
	if(tmpvar_2.x)
	{
		dest.x = 2*norm.x*norm2.x;
	}
	else
	{
		dest.x = 1-2*(1-norm.x)*(1-norm2.x);
	}
	if(tmpvar_2.y)
	{
		dest.y = 2*norm.y*norm2.y;
	}
	else
	{
		dest.y = 1-2*(1-norm.y)*(1-norm2.y);
	}
	if(tmpvar_2.z)
	{
		dest.z = 2*norm.z*norm2.z;
	}
	else
	{
		dest.z = 1-2*(1-norm.z)*(1-norm2.z);
	}
	if(tmpvar_2.w)
	{
		dest.w = 2*norm.w*norm2.w;
	}
	else
	{
		dest.w = 1-2*(1-norm.w)*(1-norm2.w);
	}
	dest = norm2 + _Opacity*(dest-norm2);
	vec3 normal = 2.0 * dest.rgb - 1.0;
	float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
	vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
	fColor = vec4(rgb, fColor.a);
}