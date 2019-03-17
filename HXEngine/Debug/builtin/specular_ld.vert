#version 430

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;

out vec2 vs_TexCoord;

void main() {
    gl_Position = vec4(position, 1.0);
    vs_TexCoord = texcoord;
}