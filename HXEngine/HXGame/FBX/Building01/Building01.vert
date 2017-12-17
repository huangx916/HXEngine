#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

// 线性雾
uniform int useFog;

uniform vec4 DiffuseColor;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;

out vec4 vs_fs_diffuse_color;
out vec2 vs_fs_texcoord;

// 线性雾
out float vs_fs_distance;

void main()
{
	gl_Position = mvp_matrix * position;
	vs_fs_diffuse_color = DiffuseColor;
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	
	// 线性雾
	if(useFog == 1)
	{
		vec4 mvPosition = view_matrix * model_matrix * position;
		vs_fs_distance = sqrt(mvPosition.x * mvPosition.x + mvPosition.y * mvPosition.y + mvPosition.z * mvPosition.z);
	}
}