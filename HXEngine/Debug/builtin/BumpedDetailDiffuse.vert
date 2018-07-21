#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

uniform vec4 MainTexture_ST;
uniform vec4 NormalMap_ST;
uniform vec4 MainTexture2_ST;
uniform vec4 NormalMap2_ST;
out vec4 vs_fs_texcoord;
out vec4 vs_fs_detailtexcoord;

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
out vec3 lightTangentDir[MaxLights];
out vec3 ConeTangentDir[MaxLights];
out float lightDistance[MaxLights];
uniform vec3 eyePos;
out vec3 eyeTangentDir;

///////////////////////////////////////////
// fog
uniform int useFog;
out float vs_fs_distance;
////////////////////////////////////////////

void main()
{
	gl_Position = mvp_matrix * vec4(position, 1);

	vs_fs_texcoord.xy = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	vs_fs_texcoord.zw = texcoord * NormalMap_ST.xy + NormalMap_ST.zw;
	vs_fs_detailtexcoord.xy = texcoord * MainTexture2_ST.xy + MainTexture2_ST.zw;
	vs_fs_detailtexcoord.zw = texcoord * NormalMap2_ST.xy + NormalMap2_ST.zw;
	
	vec3 n = normalize(normal);
    vec3 t = normalize(tangent);
    vec3 b = cross(n, t);

    vec4 worldPos = model_matrix * vec4(position, 1);

    vec3 eyeWorldDir = eyePos - worldPos.xyz;
    vec3 eyeObjectDir = normalize((vec4(eyeWorldDir,0) * model_matrix).xyz);
    vec3 v;
    v.x = dot (eyeObjectDir, t);
    v.y = dot (eyeObjectDir, b);
    v.z = dot (eyeObjectDir, n);
    //eyeTangentDir = normalize (v);
    vec3 v1 = normalize (v);
    eyeTangentDir = v1;

    for(int i = 0; i < MaxLights; ++i)
    {
        if(!Lights[i].isEnable)
        {
            continue;
        }
        if(Lights[i].lightType == 1)
        {
            // 平行光
            vec3 lightWorldDir = Lights[i].lightDir;
            //// 1	3x3正交矩阵 转置矩阵即是逆矩阵 矩阵右乘同转置矩阵左乘
            vec3 lightObjectDir = normalize((vec4(lightWorldDir,0) * model_matrix).xyz);
            // lighting tangent space
            vec3 v;
            v.x = dot (lightObjectDir, t);
            v.y = dot (lightObjectDir, b);
            v.z = dot (lightObjectDir, n);
            lightTangentDir[i] = normalize (v);
        }
        if(Lights[i].lightType == 2)
        {
            // 点光源
            vec3 lightWorldDir = Lights[i].lightPos - worldPos.xyz;
            lightDistance[i] = length(lightWorldDir);
            vec3 lightObjectDir = normalize((vec4(lightWorldDir,0) * model_matrix).xyz);
            vec3 v;
            v.x = dot (lightObjectDir, t);
            v.y = dot (lightObjectDir, b);
            v.z = dot (lightObjectDir, n);
            lightTangentDir[i] = normalize (v);
        }
        if(Lights[i].lightType == 3)
        {
            // 聚光灯
            vec3 lightWorldDir = Lights[i].lightPos - worldPos.xyz;
            lightDistance[i] = length(lightWorldDir);
            vec3 lightObjectDir = normalize((vec4(lightWorldDir,0) * model_matrix).xyz);
            vec3 v;
            v.x = dot (lightObjectDir, t);
            v.y = dot (lightObjectDir, b);
            v.z = dot (lightObjectDir, n);
            lightTangentDir[i] = normalize (v);

            vec3 ConeWorldDir = Lights[i].ConeDirection;
            vec3 ConeObjectDir = normalize((vec4(ConeWorldDir,0) * model_matrix).xyz);
            v.x = dot (ConeObjectDir, t);
            v.y = dot (ConeObjectDir, b);
            v.z = dot (ConeObjectDir, n);
            ConeTangentDir[i] = normalize (v);
        }
    }
    /////////////////////////////////////////////////////////////////
    // fog
    if(useFog == 1)
    {
        vec4 mvPosition = view_matrix * model_matrix * vec4(position, 1);
        vs_fs_distance = sqrt(mvPosition.x * mvPosition.x + mvPosition.y * mvPosition.y + mvPosition.z * mvPosition.z);
    }
    /////////////////////////////////////////////////////////////////
}