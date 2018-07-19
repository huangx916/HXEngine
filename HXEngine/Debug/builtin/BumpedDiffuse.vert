#version 430 core

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

uniform vec4 MainTexture_ST;
uniform vec4 NormalMap_ST;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent;

out vec4 vs_fs_texcoord;

///////////////////////////////////////////
// lighting world space
out vec4 vs_fs_normal;
// lighting tangent space
out vec3 vs_fs_light_dir;
///////////////////////////////////////////


void main()
{
	gl_Position = mvp_matrix * position;
	vs_fs_texcoord.xy = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;
	vs_fs_texcoord.zw = texcoord * NormalMap_ST.xy + NormalMap_ST.zw;
	
	// lighting world space TODO: 逆转置矩阵
	vs_fs_normal = model_matrix * vec4(normal,0);
	
	// lighting object space
	vec3 lightWorldDir = vec3(-1,1,1);
	//// 1	3x3正交矩阵 转置矩阵既是逆矩阵 矩阵右乘同转置矩阵左乘
	vec3 lightObjectDir = normalize((vec4(lightWorldDir,0) * model_matrix).xyz);
	//// 2
	//mat4 model_matrix_inverse = inverse_mat4(model_matrix);
	//vec3 lightObjectDir = (model_matrix_inverse * vec4(lightWorldDir,0)).xyz;
	//lightObjectDir = normalize(lightObjectDir);
	
	vec3 n = normalize(normal);
	vec3 t = normalize(tangent);
	vec3 b = cross(n, t);
	
	// lighting tangent space
	vec3 v;
	v.x = dot (lightObjectDir, t);
	v.y = dot (lightObjectDir, b);
	v.z = dot (lightObjectDir, n);
	vs_fs_light_dir = normalize (v);	
}