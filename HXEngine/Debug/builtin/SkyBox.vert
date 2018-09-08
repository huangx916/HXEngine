#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

uniform vec4 DiffuseColor;
//uniform vec4 MainTexture_ST;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

out vec4 vs_fs_diffuse_color;
out vec2 vs_fs_texcoord;
out vec3 vs_fs_normal;

///////////////////////////////////////////////////////
//// fog
//uniform int useFog;
//out float vs_fs_distance;
///////////////////////////////////////////////////////

void main()
{
	gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_diffuse_color = DiffuseColor;
	//vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	vs_fs_texcoord = texcoord;
	vs_fs_normal = normal;
	
	/////////////////////////////////////////////////////////////////
	//// fog
	//if(useFog == 1)
	//{
	//	vec4 mvPosition = view_matrix * model_matrix * position;
	//	vs_fs_distance = sqrt(mvPosition.x * mvPosition.x + mvPosition.y * mvPosition.y + mvPosition.z * mvPosition.z);
	//}
	/////////////////////////////////////////////////////////////////
}