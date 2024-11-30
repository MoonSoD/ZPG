#version 330

in vec4 ex_worldPos;  
in vec3 ex_worldNorm;

out vec4 out_Color;

struct Light {
    int type;              
    vec3 ambient;           
    vec3 diffuse;           
    vec3 specular;          
    vec3 position;          
    vec3 direction;    
    vec3 color;             
    float constantAttenuation; 
    float linearAttenuation;   
    float quadraticAttenuation; 
    float innerConeAngle;   
    float outerConeAngle;  
};

uniform Light light[3];  

uniform vec3 viewPosition; 
uniform vec3 cameraTarget; 

uniform vec3 objectColor; 

uniform mat4 viewMatrix;

void main(void) {
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 finalColor = vec3(0.0);

    vec3 lightVector;

    for (int i = 0; i < 3; i++) {  
        Light currentLight = light[i];

        float attenuation = 1.0;

        if (currentLight.type == 1) {
            float distance = length(currentLight.position - vec3(ex_worldPos));
            attenuation = 1.0 / (currentLight.constantAttenuation + currentLight.linearAttenuation * distance + currentLight.quadraticAttenuation * distance * distance);
            lightVector = normalize(currentLight.position - vec3(ex_worldPos));
        }

        if (currentLight.type == 2) {
            lightVector = normalize(-currentLight.direction);  
        }
        
        if (currentLight.type == 3) {
            currentLight.position = viewPosition; 
            vec3 spotDir = cameraTarget; 

            lightVector = normalize(currentLight.position - ex_worldPos.xyz); 
            
            float spotEffect = dot(normalize(-spotDir), lightVector); 
            
            if (spotEffect < cos(currentLight.outerConeAngle)) {
                spotEffect = 0.0;
            } else if (spotEffect > cos(currentLight.innerConeAngle)) {
                spotEffect = 1.0;
            } else {
                float epsilon = cos(currentLight.innerConeAngle) - cos(currentLight.outerConeAngle);
                spotEffect = (spotEffect - cos(currentLight.outerConeAngle)) / epsilon;
            }

            attenuation *= spotEffect;
        }

        ambient += currentLight.ambient * objectColor * attenuation;

        vec3 norm = normalize(ex_worldNorm); 
        float diffIntensity = max(dot(lightVector, norm), 0.0);
        diffuse += diffIntensity * currentLight.diffuse * currentLight.color * attenuation;

        float specularStrength = 0.5; 
        float shininess = 32.0;      
        vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos)); 
        vec3 reflectDir = reflect(-lightVector, norm); 
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
        specular += specularStrength * spec * currentLight.specular * attenuation;
    }

    finalColor = ambient + diffuse + specular;

    out_Color = vec4(finalColor, 1.0);
}
