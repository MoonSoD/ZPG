# version 330
// atribut 0 in VAO
layout(location = 0) in vec3 vp; // position

out vec3 fragPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform bool lockSkybox;

void main()
{
	mat4 view = viewMatrix;
	view[3][0] = 0.0;
	view[3][1] = 0.0;
	view[3][2] = 0.0;

	gl_Position = projectionMatrix * view * vec4 (vp, 1.0);
    fragPosition = vp;
}