#version 430 core

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;

in vec4 vs_fs_diffuse_color;
in vec2 vs_fs_texcoord;
in vec3 vs_fs_normal;

out vec4 fColor;

/////////////////////////////////////////////////////
//// fog
//uniform int useFog;
//uniform int fogType;
//uniform vec3 fogColor;
//uniform float fogStart;
//uniform float fogEnd;
//in float vs_fs_distance;
/////////////////////////////////////////////////////

void main()
{
	//fColor = vec4(0.0, 1.0, 0.0, 1.0);
	//fColor = vec4(vs_fs_texcoord.x, vs_fs_texcoord.y, 0, 1);
	//fColor = texture(Texture1, vs_fs_texcoord);
	
	//fColor = vec4(vs_fs_normal.x, vs_fs_normal.y, vs_fs_normal.z, 1);
	
	if(vs_fs_normal.y > 0.5)
	{
		//fColor = vec4(0.0, 1.0, 0.0, 1.0);
		fColor = texture(Texture5, vs_fs_texcoord);
	}
	if(vs_fs_normal.y < -0.5)
	{
		//fColor = vec4(0.0, 0.5, 0.0, 1.0);
		fColor = texture(Texture6, vs_fs_texcoord);
	}
	if(vs_fs_normal.x < -0.5)
	{
		//fColor = vec4(1.0, 0.0, 0.0, 1.0);
		fColor = texture(Texture3, vs_fs_texcoord);
	}
	if(vs_fs_normal.x > 0.5)
	{
		//fColor = vec4(0.5, 0.0, 0.0, 1.0);
		fColor = texture(Texture4, vs_fs_texcoord);
	}
	if(vs_fs_normal.z > 0.5)
	{
		//fColor = vec4(0.0, 0.0, 1.0, 1.0);
		fColor = texture(Texture1, vs_fs_texcoord);
	}
	if(vs_fs_normal.z < -0.5)
	{
		//fColor = vec4(0.0, 0.0, 0.5, 1.0);
		fColor = texture(Texture2, vs_fs_texcoord);
	}
	fColor = vec4(fColor.xyz, 1);
	
	//////////////////////////////////////////////////////////////////////////////////////
	//if(useFog == 1)
	//{
	//	// linear fog
	//	if(fogType == 0)
	//	{
	//		vec4 _fogColor = vec4(fogColor, 1.0);
	//		float fog  = (vs_fs_distance - fogStart)/fogEnd;
	//		fog = clamp(fog, 0.0, 1.0);
	//		fColor = mix(fColor, _fogColor, fog);
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////////////////
}