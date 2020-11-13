#shader vertex
#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec3 _normal;

uniform mat4 u_vp;
uniform mat4 u_model;

out vec3 v_pos;
out vec3 v_normal;

void main() {
    gl_Position = u_vp * u_model * vec4(_pos.xyz, 1.0);

   // @formatter:off
    v_pos    = _pos;
    v_normal = _normal;
   // @formatter:on
}

#shader fragment
#version 330 core
in vec3 v_pos;
in vec3 v_normal;
in vec4 v_color;

uniform vec4 u_color;
uniform vec4 u_lightColor;

out vec4 color_;

void main() {
    color_ = u_lightColor * u_color;
}