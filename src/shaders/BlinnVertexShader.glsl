#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 vt;

out vec3 fragPosition;
out vec3 fragNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;

void main() {
    uv = vt;
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    vec4 worldPosition = modelMatrix * vec4(in_Position, 1.0);
    fragPosition = vec3(worldPosition);

    fragNormal = normalize(normalMatrix * in_Normal);

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}