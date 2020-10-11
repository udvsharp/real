#version 330 core

in vec3 v_pos;
in vec2 v_texcoord;

uniform sampler2D u_texture;
uniform vec4 u_color;

out vec4 color_;

void main() {
    color_ = texture(u_texture, v_texcoord);
}
