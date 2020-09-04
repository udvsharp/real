#version 330 core

in vec3 v_pos;
in vec4 v_color;

out vec4 color_;

void main() {
    color_ = v_color;
}
