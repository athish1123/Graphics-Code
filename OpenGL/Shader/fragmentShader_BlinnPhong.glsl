#version 410 core

layout(location = 0) out vec4 fragmentColor;

in vec4 normal;
in vec4 lightDir;
in vec4 worldPosition;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform vec3 ambientComponent;
uniform vec3 cameraPosWorld;
uniform float shininess;

void main(void)
{
    vec3 N = normalize(normal.xyz);
    vec3 L = normalize(lightDir.xyz);
    vec3 V = normalize(cameraPosWorld - worldPosition.xyz);
    vec3 H = normalize(L + V);

    float diffuseIntensity = max(dot(N, L), 0.0);
    float specularIntensity =
        diffuseIntensity > 0.0
            ? pow(max(dot(N, H), 0.0), shininess)
            : 0.0;

    vec3 ambient = ambientComponent * diffuseComponent;
    vec3 diffuse = diffuseComponent * diffuseIntensity;
    vec3 specular = specularComponent * specularIntensity;

    fragmentColor = vec4(ambient + diffuse + specular, 1.0);
}