#version 430 core
uniform sampler2D MainTexture;
uniform sampler2D NormalMap;
uniform vec4 DiffuseColor;
uniform vec3 ambient;

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

in vec3 lightTangentDir[MaxLights];
in vec3 ConeTangentDir[MaxLights];

in vec3 eyeTangentDir;

in vec4 vs_fs_texcoord;

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

void main()
{
    fColor = texture(MainTexture, vs_fs_texcoord.xy) * DiffuseColor;
    vec3 normal = 2.0 * texture(NormalMap, vs_fs_texcoord.zw).rgb - 1.0;

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
    }
    vec3 scatteredLight = ambi + diff;
    vec3 reflactedLight = spec;
    vec3 rgb = min(fColor.rgb * scatteredLight + reflactedLight, vec3(1.0));
    fColor = vec4(rgb, fColor.a);
    //////////////////////////////////////////////////////////////////////////////////////

//    //////////////////////////////////////////////////////////////////////////////////////
//    // 线性雾
//    if(useFog == 1)
//    {
//        // linear fog
//        if(fogType == 0)
//        {
//            vec4 _fogColor = vec4(fogColor, 1.0);
//            float fog  = (vs_fs_distance - fogStart)/fogEnd;
//            fog = clamp(fog, 0.0, 1.0);
//            fColor = mix(fColor, _fogColor, fog);
//        }
//    }
//    //////////////////////////////////////////////////////////////////////////////////////


	
//	// 法线贴图
//	fColor = texture(MainTexture, vs_fs_texcoord.xy);
//	vec3 normal = 2.0 * texture(NormalMap, vs_fs_texcoord.zw).rgb - 1.0;
//	normal = normalize(normal);
//	float diffuse = max(0.0, dot(normal, vs_fs_light_dir));
//	vec3 rgb = min(fColor.rgb * diffuse, vec3(1.0));
//	fColor = vec4(rgb, fColor.a);
}
