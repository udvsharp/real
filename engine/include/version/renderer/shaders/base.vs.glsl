#version 330 core

layout(location = 0) in vec3 _pos;

uniform mat4 u_vp;

out vec3 v_pos;

void main() {
    v_pos = _pos;
    gl_Position = u_vp * vec4(_pos.xyz, 1.0);
}
