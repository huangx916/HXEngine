#version 430

uniform sampler2D MainTexture;
uniform sampler2D NormalTex;
uniform sampler2D SmoothTex;
uniform sampler2D CurveTex;
uniform sampler2D SSSLUT;
uniform sampler2D KelemenLUT;

in vec4 uv;
in vec4 T2W0;
in vec4 T2W1;
in vec4 T2W2;

in vec3 worldNormal;
in vec3 worldTangent;
in vec3 worldBitangent;

out vec4 fColor;

uniform vec3 ambient;
uniform vec3 eyePos;

float fresnelReflectance( vec3 H, vec3 V, float F0 )
{
    float base = 1.0 - dot( V, H );
    float exponential = pow( base, 5.0 );
    return exponential + F0 * ( 1.0 - exponential );
}

void main(void)
{
    vec3 albedo = texture(MainTexture,uv.xy).rgb;
    //fColor = vec4(albedo, 1);

    vec3 tangentNormal = texture(NormalTex, uv.zw).rgb;
    vec3 bump = 2.0 * tangentNormal - 1.0;
    vec3 worldBump = normalize(vec3(dot(T2W0.xyz,bump), dot(T2W1.xyz,bump), dot(T2W2.xyz,bump)));
    vec3 worldPos  = vec3(T2W0.w,T2W1.w,T2W2.w);

    vec3 lightDir = normalize(vec3(1,1,1));
    vec3 viewDir = normalize(eyePos - worldPos);

    // CURVE_CONST
//    float _CurveFactor = 0.5;
//    float cuv = _CurveFactor;
    // CURVE_TEX
    vec4 cuv = texture(CurveTex,uv.zw);

    float NoL = dot(worldBump,lightDir);
    vec3 diffuse = texture(SSSLUT,vec2(NoL*0.5+0.5,cuv)).rgb;
    //fColor = vec4(diffuse, 1);

    vec3 _h = lightDir + viewDir;
    vec3 H = normalize(_h);
    float NoH = dot(worldBump,H);
    float _smooth = texture(SmoothTex,uv.zw).r;

    float _SpecularScale = 1;
    // SPEC_BLINPHONG
    vec3 specular = vec3(pow(max(0,NoH),10.0) * _smooth * _SpecularScale);
    // SPEC_KELEMEN
//    float PH = pow(2.0 * texture(KelemenLUT,vec2(NoH, _smooth)).r, 10.0 );
//    float F = 0.028;//fresnelReflectance( H, viewDir, 0.028 );
//    vec3 specular = vec3(max( PH * F / dot( _h, _h ), 0 ) * _SpecularScale);

    //vec3 finalColor = (ambient + (diffuse + specular) * _LightColor0.rgb * attenuation) * albedo;
    vec3 finalColor = (ambient + (diffuse + specular)) * albedo;
    fColor = vec4(finalColor, 1);

    return;
}
