#version 430

uniform sampler2D EquirectangularMap;

in vec3 vs_fs_normal;
//out vec3 color;
out vec4 oColor;

const float PI = 3.1415926536898;

vec2 sampling_equirectangular_map(vec3 n) {
    float u = atan(n.z, n.x);
    u = (u + PI) / (2.0 * PI);

    float v = asin(n.y);
    v = (v * 2.0 + PI) / (2.0 * PI);

    return vec2(u, v);
}

void main(void)
{
//	vec2 uv = sampling_equirectangular_map(normalize(vs_fs_normal));
//    color = texture2D(EquirectangularMap, uv).xyz;
//    color = color / (color + vec3(1));
//    color = pow(color, vec3(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2));

    oColor = vec4(1,0,0,1);
}
