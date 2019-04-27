#version 430

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;
uniform vec4 MainTexture_ST;
uniform vec4 NormalTex_ST;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

out vec4 vs_fs_texcoord;
out vec3 vs_Vertex;
out vec3 vs_Normal;
out vec3 vs_Tangent;
out vec3 vs_Binormal;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_texcoord.xy = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	vs_fs_texcoord.zw = texcoord * NormalTex_ST.xy + NormalTex_ST.zw;

    vs_Vertex = (model_matrix * vec4(position, 1.0)).xyz;

    mat4 invWorld = inverse(model_matrix);

	vec3 n = normalize(normal);
    vec3 t = normalize(tangent);
    //vec3 b = cross(n, t);

    vs_Normal = (invWorld * vec4(n, 0.0)).xyz;
    vs_Tangent = (invWorld * vec4(t, 0.0)).xyz;
    vs_Binormal = cross(vs_Normal, vs_Tangent);
}
