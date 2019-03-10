#version 330

uniform mat4 mvp_matrix;

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

out vec3 vs_fs_normal;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_normal = normal;
}
