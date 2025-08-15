#version 330 core

in vec3 v_color;

out vec4 out_fragColor;

uniform vec3 u_color;

void main() {
    out_fragColor = vec4(v_color, 1.0);
}
