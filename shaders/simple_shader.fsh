#version 330 core

in vec3 v_color;

out vec4 out_fragColor;

//uniform vec3 u_color;

uniform sampler2D u_texture;

in vec2 v_texcoords;

void main() {
	vec4 myTex1
    out_fragColor = texture(u_texture, v_texcoords);
	//vec4(v_color, 1.0);
}
