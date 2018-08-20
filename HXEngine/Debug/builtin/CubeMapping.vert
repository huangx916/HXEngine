#version 330

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp_matrix;

//uniform vec4 MainTexture_ST;
uniform vec3 eyePos;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

//out vec2 vs_fs_texcoord;
out vec3 reflectvec;

void main(void)
{
    gl_Position = mvp_matrix * vec4(position, 1);
	//vs_fs_texcoord = texcoord * MainTexture_ST.xy + MainTexture_ST.zw;

    vec4 worldPos = model_matrix * vec4(position, 1);
    vec3 eyeWorldDir = normalize(eyePos - worldPos.xyz);
    vec3 worldNormal = normalize((model_matrix * vec4(normal, 0)).xyz);
    reflectvec = reflect(eyeWorldDir, worldNormal);
}
