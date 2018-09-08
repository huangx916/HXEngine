#version 430 core

uniform mat4 mvp_matrix;

layout(location = 0) in vec3 vPosition;

void main()
{
	gl_Position = mvp_matrix * vec4(vPosition, 1);
}