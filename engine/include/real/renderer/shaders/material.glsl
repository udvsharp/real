#shader vertex
#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec3 _normal;

uniform mat4 u_vp;
uniform mat4 u_model;

out vec3 FragPos;
out vec3 FragNormal;

void main() {
    vec4 o_pos = u_model * vec4(_pos.xyz, 1.0);
    gl_Position = u_vp * o_pos;

   // @formatter:off
    FragPos    = vec3(o_pos);
    FragNormal = mat3(transpose(inverse(u_model))) * _normal;
   // @formatter:on
}

#shader fragment
#version 330 core
in vec3 FragPos;
in vec3 FragNormal;

uniform vec3 u_color;
uniform vec3 u_viewPos;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;

out vec4 color_;

void main() {
    vec3 normal = normalize(FragNormal);

    // Ambient Lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * u_lightColor;

    // Diffuse Lighting
    vec3 lightDir = normalize(u_lightPos - FragPos);
    vec3 diffuse = max(dot(normal, lightDir), 0.0f) * u_lightColor;

    // Specular Lighting
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(u_viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 result = (ambient + diffuse + specular) * u_color;
    color_ = vec4(result, 1.0f);
}