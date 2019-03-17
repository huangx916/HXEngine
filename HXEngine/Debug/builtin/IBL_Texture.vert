#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

uniform mat4 mvp_matrix;
//uniform mat4 glb_InvTransWorldM;
uniform mat4 model_matrix;

out vec3 vs_Vertex;
out vec2 vs_Texcoord;
out vec3 vs_Normal;
out vec3 vs_Tangent;
out vec3 vs_Binormal;

void main() {
    gl_Position = (mvp_matrix * vec4(position, 1.0));

    mat4 invWorld = inverse(model_matrix);

    //vs_Normal = cross(tangent, glb_attr_Binormal);
    vs_Binormal = cross(normal, tangent);
	vs_Tangent = (invWorld * vec4(tangent, 0.0)).xyz;
	vs_Binormal = (invWorld * vec4(vs_Binormal, 0.0)).xyz;
	vs_Normal = (invWorld * vec4(normal, 0.0)).xyz;

    vs_Vertex = (model_matrix * vec4(position, 1.0)).xyz;
    vs_Texcoord = texcoord;
}