# version 330
// atribut 0 in VAO
layout(location = 0) in vec3 vp; // position
// atribut 1 in VAO
layout(location = 1) in vec3 vn; // normal

layout(location = 2) in vec2 uv; // uv

out vec2 vt_out; 

out vec4 ex_worldPos;
out vec3 ex_worldNorm;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vt_out = uv;
	ex_worldPos = modelMatrix * vec4 ( vp ,1.0);
	mat4 normal = transpose(inverse(modelMatrix));// problem - priste vysvetlime
	ex_worldNorm = vec3 (normal * vec4 (vn, 1.0));
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
}