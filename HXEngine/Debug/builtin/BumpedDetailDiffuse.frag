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
	//fColor = texture(MainTexture, vs_fs_texcoord.xy);
	//vec3 normal = 2.0 * texture(NormalMap, vs_fs_texcoord.zw).rgb - 1.0;
	//normal = normalize(normal);
	//float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
	
	//fColor = texture(MainTexture, vs_fs_texcoord.xy);
	//vec3 lightDir = vec3(-1,1,1);
	//vec3 normal = normalize(vs_fs_normal.xyz);
	//float diffuse = max(0.0, dot(normal, lightDir));
	
	
	float _Opacity = 1.0;
	vec4 _Color = vec4(1,1,1,1);
	vec4 tex2 = texture(MainTexture, vs_fs_texcoord.xy);
	vec4 tex = texture(MainTexture2, vs_fs_detailtexcoord.xy);
	vec4 dest;
	_Opacity*=tex.a;
	//dest.rgb = tex2.rgb <= 0.5 ? 2*tex.rgb*tex2.rgb : 1-2*(1-tex.rgb)*(1-tex2.rgb);
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
	//dest.rgb = lerp(tex2.rgb, dest.rgb, _Opacity);
	dest.rgb = tex2.rgb + _Opacity*(dest.rgb-tex2.rgb);
	dest.rgb *= _Color.rgb;
	//o.Albedo = dest.rgb;
	fColor.rgb = dest.rgb;
	//o.Alpha = tex2.a * _Color.a;
	fColor.a = tex2.a * _Color.a;
   
	vec4 norm2 = texture(NormalMap, vs_fs_texcoord.zw);
	vec4 norm = texture(NormalMap2, vs_fs_detailtexcoord.zw);
	//dest = norm2<=0.5 ? 2*norm*norm2 : 1-2*(1-norm)*(1-norm2);
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
	//dest = lerp(norm2, dest, _Opacity);
	dest = norm2 + _Opacity*(dest-norm2);
	//o.Normal = UnpackNormal(dest);
	vec3 normal = 2.0 * dest.rgb - 1.0;
	float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
	
	
	vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
	fColor = vec4(rgb, fColor.a);
	
}