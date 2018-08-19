#version 430 core

uniform sampler2D MainTexture;
uniform sampler2D NormalMap;
uniform sampler2D MainTexture2;
uniform sampler2D NormalMap2;
uniform vec4 DiffuseColor;
uniform vec3 ambient;
in vec4 vs_fs_texcoord;
in vec4 vs_fs_detailtexcoord;

struct LightInfo
{
    bool isEnable;
    int lightType;
    vec3 lightColor;
    vec3 lightDir;
    float shininess;
    float strength;
    vec3 lightPos;
    float constantAttenuation;	// 衰减系数
    float LinearAttenuation;
    float QuadraticAttenuation;
    vec3 ConeDirection;
    float SpotCosCutoff;
    float SpotExponent;
};
const int MaxLights = 5;
uniform LightInfo Lights[MaxLights];
in vec3 lightTangentDir[MaxLights];
in vec3 ConeTangentDir[MaxLights];
in float lightDistance[MaxLights];
in vec3 eyeTangentDir;

/////////////////////////////////////////////////////
// fog
uniform int useFog;
uniform int fogType;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;
uniform float fogDensity;
uniform float fogGradiant;
in float vs_fs_distance;
/////////////////////////////////////////////////////

out vec4 fColor;

void DirectionalLight(vec3 eyeDir, vec3 lightDir, vec3 normal, vec3 lightColor, float shininess, float strength, inout vec3 diff, inout vec3 spec)
{
	vec3 halfDir = normalize(eyeDir + lightDir);
	float diffuse = max(0.0, dot(normal, lightDir));
	float specular = max(0.0, dot(normal, halfDir));
	if(diffuse == 0.0)
	{
		specular = 0.0;
	}
	else
	{
		specular = pow(specular, shininess) * strength;
	}

	diff += lightColor * diffuse;
	spec += lightColor * specular;
	//spec = vec3(0);
}

void PointLight(vec3 eyeDir, vec3 lightDir, float lightDistance, vec3 normal, vec3 lightColor, float shininess, float strength,
float constantAttenuation, float LinearAttenuation, float QuadraticAttenuation, inout vec3 diff, inout vec3 spec)
{
	float attenuation = 1.0 / (constantAttenuation + LinearAttenuation*lightDistance + QuadraticAttenuation*lightDistance*lightDistance);
	vec3 halfDir = normalize(lightDir + eyeDir);
	float diffuse = max(0.0, dot(normal, lightDir));
	float specular = max(0.0, dot(normal, halfDir));
	if(diffuse == 0.0)
	{
		specular = 0.0;
	}
	else
	{
		specular = pow(specular, shininess) * strength;
	}

	//attenuation = 0.2;
	diff += lightColor * diffuse * attenuation;
	spec += lightColor * specular * attenuation;
}

void SpotLight(vec3 eyeDir, vec3 lightDir, float lightDistance, vec3 normal, vec3 lightColor, float shininess, float strength,
float constantAttenuation, float LinearAttenuation, float QuadraticAttenuation,
vec3 ConeDirection, float SpotCosCutoff, float SpotExponent, inout vec3 diff, inout vec3 spec)
{
	float attenuation = 1.0 / (constantAttenuation + LinearAttenuation*lightDistance + QuadraticAttenuation*lightDistance*lightDistance);
	float spotCos = dot(lightDir, -ConeDirection);
	if(spotCos < SpotCosCutoff)
	{
		attenuation = 0.0;
	}
	else
	{
		attenuation *= pow(spotCos, SpotExponent);
	}
	vec3 halfDir = normalize(lightDir + eyeDir);
	float diffuse = max(0.0, dot(normal, lightDir));
	float specular = max(0.0, dot(normal, halfDir));
	if(diffuse == 0.0)
	{
		specular = 0.0;
	}
	else
	{
		specular = pow(specular, shininess) * strength;
	}

	//attenuation = 1;
	diff += lightColor * diffuse * attenuation;
	spec += lightColor * specular * attenuation;
}

void main()
{
	float _Opacity = 1.0;
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
	dest.rgb *= DiffuseColor.rgb;
	fColor.rgb = dest.rgb;
	fColor.a = tex2.a * DiffuseColor.a;
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

	//////////////////////////////////////////////////////////////////////////////////////
    // 光照处理 世界坐标系下
    vec3 ambi = ambient;
    vec3 diff = vec3(0);
    vec3 spec = vec3(0);
    for(int i = 0; i < MaxLights; ++i)
    {
        if(!Lights[i].isEnable)
        {
            continue;
        }
        if(Lights[i].lightType == 1)
        {
            // 平行光
            DirectionalLight(normalize(eyeTangentDir), normalize(lightTangentDir[i]), normalize(normal), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength, diff, spec);
        }
        else if(Lights[i].lightType == 2)
        {
            // 点光源
            PointLight(normalize(eyeTangentDir), normalize(lightTangentDir[i]), lightDistance[i], normalize(normal), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength, Lights[i].constantAttenuation, Lights[i].LinearAttenuation, Lights[i].QuadraticAttenuation, diff, spec);
        }
        else if(Lights[i].lightType == 3)
        {
            // 聚光灯
            SpotLight(normalize(eyeTangentDir), normalize(lightTangentDir[i]), lightDistance[i], normalize(normal), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength,
            Lights[i].constantAttenuation, Lights[i].LinearAttenuation, Lights[i].QuadraticAttenuation,
            normalize(ConeTangentDir[i]), Lights[i].SpotCosCutoff, Lights[i].SpotExponent, diff, spec);
        }
    }
    vec3 scatteredLight = ambi + diff;
    vec3 reflactedLight = spec;
    vec3 rgb = min(fColor.rgb * scatteredLight + reflactedLight, vec3(1.0));
    fColor = vec4(rgb, fColor.a);
    //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////
    if(useFog == 1)
    {
        vec4 _fogColor = vec4(fogColor, 1.0);
        float factor = 0;
        if(fogType == 0)
        {
            // linear fog
            factor  = (vs_fs_distance - fogStart)/(fogEnd - fogStart);
        }
        else if(fogType == 1)
        {
            // exp fog
            factor = 1 - exp(-vs_fs_distance * fogDensity);

        }
        else if(fogType == 2)
        {
            // expx fog
            factor = 1 - exp(-pow(vs_fs_distance * fogDensity, fogGradiant));
        }
        factor = clamp(factor, 0.0, 1.0);
        fColor = mix(fColor, _fogColor, factor);
    }
    //////////////////////////////////////////////////////////////////////////////////////
}