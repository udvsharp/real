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
    FragNormal = mat3(transpose(inverse(u_model))) * _normal; // TODO: calcaulate this in CPU
   // @formatter:on
}

#shader fragment
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 FragNormal;

uniform vec3 u_viewPos;
uniform Material u_Material;
uniform Light u_Light;

out vec4 color_;

void main() {
//    vec3 outColor = vec3(0.0f);
//    outColor += calculateDirectionalLight();
//    for (int i = 0; i < nr_of_point_lights; i++) {
//        outColor += calculatePointLight();
//    }
//    outColor += calculateSpotLight();

    vec3 normal = normalize(FragNormal);

    // TODO: view space calculations?
    // Diffuse Lighting
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0f);

    // Specular Lighting
    vec3 viewDir = normalize(u_viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);

    // Components
    vec3 ambient  = u_Light.ambient * u_Material.ambient;
    vec3 diffuse  = u_Light.diffuse * (diff * u_Material.diffuse);
    vec3 specular = u_Light.specular * (spec * u_Material.specular);

    vec3 result = ambient + diffuse + specular;
    color_ = vec4(result, 1.0f);
}