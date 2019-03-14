#version 430

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

uniform mat4 mvp_matrix;
//uniform mat4 hx_InvTransWorldM;
uniform mat4 hx_World;

out vec3 vs_Vertex;
out vec3 vs_Normal;

void main() {
    gl_Position = (mvp_matrix * vec4(position, 1.0));

    //vs_Normal = (hx_InvTransWorldM * vec4(normal, 0.0)).xyz;
    mat4 invWorld = inverse(hx_World);
    vs_Normal = (invWorld * vec4(normal, 0.0)).xyz;

    vs_Vertex = (hx_World * vec4(position, 1.0)).xyz;
}