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
layout (location = 3) in vec3 normal;

out vec4 vs_fs_diffuse_color;
out vec2 vs_fs_texcoord;

// 光照 世界空间
out vec4 vs_fs_normal;
out vec4 vs_fs_position;

// 线性雾
out float vs_fs_distance;

void main()
{
	gl_Position = mvp_matrix * position;
	vs_fs_diffuse_color = DiffuseColor;
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	// TODO: 逆转置矩阵
	vs_fs_normal = model_matrix * vec4(normal,0);
	vs_fs_position = model_matrix * position;
	
	// 线性雾
	if(useFog == 1)
	{
		vec4 mvPosition = view_matrix * model_matrix * position;
		vs_fs_distance = sqrt(mvPosition.x * mvPosition.x + mvPosition.y * mvPosition.y + mvPosition.z * mvPosition.z);
	}
}