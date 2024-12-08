#version 330

in vec4 ex_worldPos;  
in vec3 ex_worldNorm;

out vec4 out_Color;

struct Light {
    int type;              
    
    vec3 position;          
    vec3 direction;    

    float constantAttenuation; 
    float linearAttenuation;   
    float quadraticAttenuation; 
    
    float cutoffAngle;
};

uniform Light light[4];  

uniform vec3 viewPosition; 
uniform vec3 cameraTarget; 

uniform vec3 objectColor; 

uniform vec3 r_a;
uniform vec3 r_d;
uniform vec3 r_s;

uniform mat4 viewMatrix;

uniform sampler2D textureUnitID;

in vec2 uv;

void main(void) {
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec4 finalColor = vec4(0.0);

    vec3 lightVector;

    for (int i = 0; i < 4; i++) {  
        Light currentLight = light[i];

        float attenuation = 1.0;

        if (currentLight.type == 1) {
            float distance = length(currentLight.position - vec3(ex_worldPos));
            attenuation = 1.0 / (currentLight.constantAttenuation + currentLight.linearAttenuation * distance + currentLight.quadraticAttenuation * distance * distance);
            lightVector = normalize(currentLight.position - vec3(ex_worldPos));
        }

        if (currentLight.type == 2) {
            lightVector = normalize(-currentLight.direction);  
            attenuation = 1.0;
        }
        
        if (currentLight.type == 3) {
            currentLight.position = viewPosition;
            vec3 spotlightVector = cameraTarget; 

            lightVector = normalize(currentLight.position - vec3(ex_worldPos));

            float spotEffect = dot(normalize(-spotlightVector), lightVector);

            if (spotEffect < cos(currentLight.cutoffAngle)) {
                attenuation = 0.0; 
            } 
        }

        ambient += r_a * objectColor * attenuation;

        vec3 norm = normalize(ex_worldNorm); 
        float diffIntensity = max(dot(lightVector, norm), 0.0);
        diffuse += r_d * diffIntensity * objectColor * attenuation;

        float specularStrength = 0.5; 
        float shininess = 32.0;      

        vec3 cameraDirection = normalize(viewPosition - vec3(ex_worldPos)); 
        vec3 reflectionDirection = reflect(-lightVector, norm); 

        float specWithoutShine = max(dot(cameraDirection, reflectionDirection), 0.0);
        float spec = pow(specWithoutShine, shininess);

        specular += r_s * specularStrength * spec * attenuation;
    }

    finalColor = vec4(ambient + diffuse + specular, 1.0);
    
    if (length(uv) > 0.0) {
        out_Color = texture(textureUnitID, uv) * finalColor;
    } else {
        out_Color = finalColor;
    }
}