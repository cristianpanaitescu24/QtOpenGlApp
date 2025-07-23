#version 330 core

layout(location = 0) in vec2 a_position;

uniform float u_size;

void main() {
    gl_Position = vec4(a_position.x * u_size, a_position.y, 0.0, 1.0);
}
