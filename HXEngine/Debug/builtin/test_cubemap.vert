#version 330

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

uniform mat4 mvp_matrix;

out vec3 vs_Normal;

void main() {
    gl_Position = (mvp_matrix * vec4(position, 1.0));
    vs_Normal = normal;
}