#version 330

in vec3 fragPosition;

uniform samplerCube textureUnitID;

out vec4 frag_colour;

void main () {
    //TODO: attenuate skybox
    frag_colour = texture(textureUnitID, fragPosition) * vec4(0.4, 0.4, 0.4, 1.0);
}

