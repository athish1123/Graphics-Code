#version 410 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 normal;
out vec4 lightDir;

uniform mat4 projMatrix, viewMatrix, modelMatrix, normalMatrix;
uniform vec4 lightPosWorld;

void main(void)
{
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));

  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  lightDir = normalize(lightPosWorld - vertexWorldPos);

  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}
