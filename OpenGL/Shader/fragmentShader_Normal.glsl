#version 410 core

layout(location = 0) out vec4 fragmentColor;

in vec4 normal;

void main(void)
{
    vec3 normalizedNormal = normalize(normal.xyz);
    vec3 normalColor = normalizedNormal * 0.5 + 0.5;

    fragmentColor = vec4(normalColor, 1.0);
}