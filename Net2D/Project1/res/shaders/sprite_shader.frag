// sprite.frag
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D currentTexture;

void main() {
    FragColor = texture(currentTexture, TexCoord); // White color for now
}