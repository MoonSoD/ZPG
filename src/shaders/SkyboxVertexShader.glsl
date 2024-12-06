# version 330
// atribut 0 in VAO
layout(location = 0) in vec3 vp; // position

out vec3 fragPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform vec3 viewPosition;

uniform bool lockSkybox;

void main()
{	
    mat4 skyboxViewMatrix = mat4(mat3(viewMatrix)); 

	gl_Position = projectionMatrix * skyboxViewMatrix * vec4(vp, 1.0);
    fragPosition = vp;
}