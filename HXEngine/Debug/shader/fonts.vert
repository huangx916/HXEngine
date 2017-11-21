#version 430 core

uniform mat4 mvp_matrix;
uniform vec3 fontColor;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
//layout(location = 2) in vec4 vColor;

//out vec4 vs_fs_color;
out vec2 vs_fs_TexCoord;
out vec3 vs_fs_FontColor;

void main()
{
	gl_Position = mvp_matrix * vPosition;
	//vs_fs_color = vColor;
	vs_fs_TexCoord = vTexCoord;
	vs_fs_FontColor = fontColor;
}