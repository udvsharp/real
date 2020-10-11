#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec2 _texcoord;

uniform mat4 u_vp;
uniform mat4 u_model;

out vec3 v_pos;
out vec2 v_texcoord;

void main() {
    v_pos = _pos;
    v_texcoord = _texcoord;
    gl_Position = u_vp * u_model * vec4(_pos.xyz, 1.0);
}
