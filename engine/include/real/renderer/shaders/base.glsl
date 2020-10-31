#shader fragment
#version 330 core
in vec3 v_pos;

uniform vec4 u_color;

out vec4 color_;

void main() {
    color_ = u_color;
}

#shader vertex
#version 330 core

layout(location = 0) in vec3 _pos;

uniform mat4 u_vp;
uniform mat4 u_model;

out vec3 v_pos;

void main() {
    v_pos = _pos;
    gl_Position = u_vp * u_model * vec4(_pos.xyz, 1.0);
}
