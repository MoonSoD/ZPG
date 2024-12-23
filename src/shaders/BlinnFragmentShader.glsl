#version 330 core
in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform sampler2D textureUnitID;

in vec2 uv;

out vec4 fragColor;

void main() {
    vec3 lightDir = normalize(lightPosition - fragPosition);
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPosition - fragPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * vec4(0.385, 0.647, 0.812, 1.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec4 specular = spec * vec4(1.0, 1.0, 1.0, 1.0);


    if (length(uv) > 0.0) {
        vec4 textureColor = texture(textureUnitID, uv);
        fragColor = textureColor * (diffuse + specular);
    } else {
        fragColor = diffuse + specular;
    }

}