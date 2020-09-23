#version 330 core

in vec3 v_pos;

uniform vec4 u_color;

out vec4 color_;

void main() {
    color_ = u_color;
}
