#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 out_Color;

uniform vec3 viewPosition;
uniform vec3 lightPosition;  
uniform vec3 objectColor; 

void main(void) {
    //vec3 lightPosition = vec3(0.0, 0.0, 0.0);  
    vec3 lightColor = vec3(1.0, 1.0, 1.0);        
    //vec3 objectColor = vec3(0.385, 0.647, 0.812); 

    // Viewer position (could be set as a uniform)
    //vec3 viewPosition = vec3(0.0, 0.0, 0.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objectColor;

    float distance = length(lightPosition - vec3(ex_worldPos));

    float constantAttenuation = 0.1;
    float linearAttenuation = 0.09;
    float quadraticAttenuation = 0.032;

    //1/(kc+kld+kqd^2)
    float attenuation = 1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);

    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPos));
    vec3 norm = normalize(ex_worldNorm);

    float dot_product = max(dot(lightVector, norm), 0.0);
    vec3 diffuse = dot_product * lightColor * objectColor;

    float specularStrength = 0.5;
    float shininess = 32.0;
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    vec3 reflectDir = reflect(-lightVector, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = (ambient + diffuse + specular) * attenuation;
    out_Color = vec4(finalColor, 1.0);
}
