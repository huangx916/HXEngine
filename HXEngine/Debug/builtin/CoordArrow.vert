#version 330

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;
uniform vec4 MainTexture_ST;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

out vec2 vs_fs_texcoord;

void main(void)
{
    //vec3 pos = position + normal;
    gl_Position = mvp_matrix * vec4(position, 1);
	vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;

    vec4 mvPosition = view_matrix * model_matrix * vec4(position, 1);
	float distance = sqrt(mvPosition.x * mvPosition.x + mvPosition.y * mvPosition.y + mvPosition.z * mvPosition.z);
}
