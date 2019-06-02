#version 430

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;
uniform vec4 MainTexture_ST;
uniform vec4 NormalTex_ST;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

out vec4 uv;
out vec4 T2W0;
out vec4 T2W1;
out vec4 T2W2;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
	uv.xy = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	uv.zw = texcoord * NormalTex_ST.xy + NormalTex_ST.zw;
    //mat4 invWorld = inverse(model_matrix);
    vec3 worldPos = (model_matrix * vec4(position, 1.0)).xyz;
	vec3 n = normalize(normal);
    vec3 t = normalize(tangent);
    vec3 worldNormal = (model_matrix * vec4(n, 0.0)).xyz;
    vec3 worldTangent = (model_matrix * vec4(t, 0.0)).xyz;
    vec3 worldBitangent = cross(worldNormal, worldTangent);
    T2W0 = vec4(worldTangent.x, worldBitangent.x, worldNormal.x, worldPos.x);
    T2W1 = vec4(worldTangent.y, worldBitangent.y, worldNormal.y, worldPos.y);
    T2W2 = vec4(worldTangent.z, worldBitangent.z, worldNormal.z, worldPos.z);
}
