#version 330 core

out vec4 out_fragColor;

uniform vec3 u_color;

void main() {
    out_fragColor = vec4(u_color, 1.0);
}
