#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec3 a_color;

out vec3 v_color;

uniform vec2 u_positionOffset;

void main() {
    gl_Position = vec4(a_position.x + u_positionOffset.x, a_position.y + u_positionOffset.y, 0.0, 1.0);
	v_color = a_color;
}
