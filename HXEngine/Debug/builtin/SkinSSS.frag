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


void main(void)
{
    vec3 albedo = texture(MainTexture,uv.xy).rgb;
    fColor = vec4(albedo, 1);

//    //vec3 normal = texture(NormalTex, uv.zw).rgb;
//    vec3 normal = 2.0 * texture(NormalTex, uv.zw).rgb - 1.0;
//    //fColor = vec4(normal, 1);
//
//
//    vec3 worldPos  = vec3(T2W0.w,T2W1.w,T2W2.w);
//    //fColor = vec4(worldPos, 1);

    return;
}
