#version 330

in vec2 vt_out;
in vec3 fragPosition;

uniform samplerCube textureUnitID;

out vec4 frag_colour;

void main () {
    frag_colour = texture(textureUnitID, fragPosition);
}

