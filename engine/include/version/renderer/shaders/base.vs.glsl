#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec4 _color;

out vec3 v_pos;
out vec4 v_color;

void main() {
    v_pos = _pos;
    gl_Position = vec4(_pos.xyz, 1.0);
    v_color = _color;
}
