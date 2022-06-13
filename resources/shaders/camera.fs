#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform bool outline = false;

uniform sampler2D textureDiffuse;

void main()
{
    // ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = texture(textureDiffuse, TexCoords);
    if (FragColor.rgb == vec3(0.0f)) // if texture is not loaded
        FragColor += vec4(result, 1.0f);
    if (outline)
        FragColor = vec4(vec3(1.0f, 1.0f, 1.0f), 0.33f);
}
