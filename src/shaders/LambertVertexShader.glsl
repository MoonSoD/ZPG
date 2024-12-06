#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 vt;

out vec3 fragNormal;
out vec3 fragPosition;
 
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;

void main() {
    uv = vt;

    fragPosition = vec3(modelMatrix * vec4(position, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
    gl_Position = projectionMatrix * viewMatrix * vec4(fragPosition, 1.0);
}