#version 330

in vec3 fragPosition;

uniform samplerCube textureUnitID;

out vec4 frag_colour;

void main () {
    //TODO: attenuate skybox
    frag_colour = texture(textureUnitID, fragPosition);
}

