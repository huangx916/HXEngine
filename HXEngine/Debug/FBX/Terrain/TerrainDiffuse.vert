#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

uniform vec4 DiffuseColor;

uniform vec4 Layer1_ST;
uniform vec4 Layer2_ST;
uniform vec4 Layer3_ST;
uniform vec4 Layer4_ST;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;

out vec4 vs_fs_diffuse_color;
out vec4 vs_fs_vertex_color;

out vec2 vs_fs_ControlTexcoord;
out vec4 vs_fs_Layer12Texcoord;
out vec4 vs_fs_Layer34Texcoord;

void main()
{
	gl_Position = mvp_matrix * position;
	
	vs_fs_diffuse_color = DiffuseColor;
	vs_fs_vertex_color = color;
	
	vs_fs_ControlTexcoord = texcoord;
	vs_fs_Layer12Texcoord.xy = texcoord * Layer1_ST.xy + Layer1_ST.zw;
	vs_fs_Layer12Texcoord.zw = texcoord * Layer2_ST.xy + Layer2_ST.zw;
	vs_fs_Layer34Texcoord.xy = texcoord * Layer3_ST.xy + Layer3_ST.zw;
	vs_fs_Layer34Texcoord.zw = texcoord * Layer4_ST.xy + Layer4_ST.zw;
	
}