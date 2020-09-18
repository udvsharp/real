#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec4 _color;

uniform mat4 u_vp;

out vec3 v_pos;
out vec4 v_color;

void main() {
    v_pos = _pos;
    v_color = _color;
    gl_Position = u_vp * vec4(_pos.xyz, 1.0);
}
