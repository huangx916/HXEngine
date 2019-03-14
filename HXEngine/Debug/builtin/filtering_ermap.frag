#version 330

in vec3 vs_fs_normal;

out vec3 oColor;

uniform sampler2D EquirectangularMap;

const float PI = 3.1415926536898;

vec2 sampling_equirectangular_map(vec3 n) {
    float u = atan(n.z, n.x);
    u = (u + PI) / (2.0 * PI);

    float v = asin(n.y);
    v = (v * 2.0 + PI) / (2.0 * PI);

    return vec2(u, v);
}

void main() {
    vec2 uv = sampling_equirectangular_map(normalize(vs_fs_normal));
    oColor = texture2D(EquirectangularMap, uv).xyz;
}