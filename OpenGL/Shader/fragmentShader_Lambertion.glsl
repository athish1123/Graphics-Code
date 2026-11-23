#version 410 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec4 lightPosWorld2;

in vec4 normal;
in vec4 lightDir;
in vec4 worldPosition;

void main(void)
{
  vec3 N = normalize(normal.xyz);
  vec3 L1 = normalize(lightDir.xyz);
  vec3 L2 = normalize(lightPosWorld2.xyz - worldPosition.xyz);

  float val1 = max(0.0, dot(N, L1));
  float val2 = max(0.0, dot(N, L2));

  vec3 diffuseShading =
      diffuseComponent * (val1 + 0.4 * val2);
  vec3 ambient = 0.1 * diffuseComponent;

  fragmentColor = vec4(ambient + diffuseShading, 1.0);
}