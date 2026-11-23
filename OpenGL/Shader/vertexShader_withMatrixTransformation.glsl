#version 410 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 normal;
out vec4 lightDir;
out vec4 worldPosition;

uniform mat4 projMatrix, viewMatrix, modelMatrix, normalMatrix;
uniform vec4 lightPosWorld;
uniform vec4 lightPosWorld2;

void main(void)
{
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));

  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  worldPosition = vertexWorldPos;
  lightDir = normalize(lightPosWorld - vertexWorldPos);

  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}
