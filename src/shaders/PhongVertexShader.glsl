# version 330
// atribut 0 in VAO
layout(location = 0) in vec3 vp; // position
// atribut 1 in VAO
layout(location = 1) in vec3 vn; // normal

layout(location = 2) in vec2 vt;  // texture space

out vec4 ex_worldPos;
out vec3 ex_worldNorm;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;

void main()
{
	uv = vt;
	ex_worldPos = modelMatrix * vec4 ( vp ,1.0);
	mat4 normal = transpose(inverse(modelMatrix));
	ex_worldNorm = vec3 (normal * vec4 (vn, 1.0));
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
}