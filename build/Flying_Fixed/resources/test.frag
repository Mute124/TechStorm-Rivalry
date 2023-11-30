uniform vec3 lightPos;
uniform vec3 lightColor;
varying vec3 FragPos;
varying vec3 Normal;

void main()
{
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(-FragPos);
    vec3 normal = normalize(Normal);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    float diffuseStrength = 0.8;
    float diffuse = diffuseStrength * max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 specularColor = vec3(1.0);
    float specularStrength = 0.5;
    float specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 result = (ambient + diffuse + specular) * lightColor;
    gl_FragColor = vec4(result, 1.0);
}
