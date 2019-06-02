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

out vec4 fColor;

uniform vec3 ambient;
uniform vec3 eyePos;

void main(void)
{
    vec3 albedo = texture(MainTexture,uv.xy).rgb;
    //fColor = vec4(albedo, 1);

    vec3 tangentNormal = texture(NormalTex, uv.zw).rgb;
    vec3 bump = 2.0 * tangentNormal - 1.0;
    vec3 worldBump = normalize(vec3(dot(T2W0.xyz,bump), dot(T2W1.xyz,bump), dot(T2W2.xyz,bump)));
    fColor = vec4(worldBump, 1);

    vec3 worldPos  = vec3(T2W0.w,T2W1.w,T2W2.w);
    //fColor = vec4(worldPos, 1);

    vec3 lightDir = normalize(vec3(1,1,1));
    vec3 viewDir = normalize(eyePos - worldPos);

    return;
}
