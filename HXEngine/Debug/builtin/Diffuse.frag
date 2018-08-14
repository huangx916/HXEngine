#version 430 core

uniform sampler2D MainTexture;
in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;
out vec4 fColor;

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

/////////////////////////////////////////////////////
// lighting world space
uniform vec3 ambient;
uniform vec3 eyePos;
in vec4 vs_fs_normal;
in vec4 vs_fs_position;
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
const int MaxLights = 10;
uniform LightInfo Lights[MaxLights];
/////////////////////////////////////////////////////

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

void PointLight(vec3 eyeDir, vec3 lightDir, vec3 normal, vec3 lightColor, float shininess, float strength,
float constantAttenuation, float LinearAttenuation, float QuadraticAttenuation, inout vec3 diff, inout vec3 spec)
{
	float lightDistance = length(lightDir);
	lightDir = lightDir/lightDistance;
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

void SpotLight(vec3 eyeDir, vec3 lightDir, vec3 normal, vec3 lightColor, float shininess, float strength,
float constantAttenuation, float LinearAttenuation, float QuadraticAttenuation, 
vec3 ConeDirection, float SpotCosCutoff, float SpotExponent, inout vec3 diff, inout vec3 spec)
{
	float lightDistance = length(lightDir);
	lightDir = lightDir/lightDistance;
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
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	fColor = texture(MainTexture, vs_fs_texcoord) * vs_fs_diffuse_color;
	
	//////////////////////////////////////////////////////////////////////////////////////
	// 光照处理 世界坐标系下
	vec3 ambi = ambient;
	vec3 diff = vec3(0);
	vec3 spec = vec3(0);
	vec3 eyeDir = eyePos - vs_fs_position.xyz;
	for(int i = 0; i < MaxLights; ++i)
	{
		if(!Lights[i].isEnable)
		{
			continue;
		}
		if(Lights[i].lightType == 1)
		{
			// 平行光
			DirectionalLight(normalize(eyeDir), normalize(Lights[i].lightDir), normalize(vs_fs_normal.xyz), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength, diff, spec);
		}
		else if(Lights[i].lightType == 2)
		{
			// 点光源
			vec3 lightDir = Lights[i].lightPos - vs_fs_position.xyz;
			PointLight(normalize(eyeDir), lightDir, normalize(vs_fs_normal.xyz), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength, Lights[i].constantAttenuation, Lights[i].LinearAttenuation, Lights[i].QuadraticAttenuation, diff, spec);
		}
		else if(Lights[i].lightType == 3)
		{
			// 聚光灯
			vec3 lightDir = Lights[i].lightPos - vs_fs_position.xyz;
			SpotLight(normalize(eyeDir), lightDir, normalize(vs_fs_normal.xyz), Lights[i].lightColor, Lights[i].shininess, Lights[i].strength, 
			Lights[i].constantAttenuation, Lights[i].LinearAttenuation, Lights[i].QuadraticAttenuation, 
			normalize(Lights[i].ConeDirection), Lights[i].SpotCosCutoff, Lights[i].SpotExponent, diff, spec);
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