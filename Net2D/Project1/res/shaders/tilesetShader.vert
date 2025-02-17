// sprite.vert
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;

uniform vec2 textureOffset;
uniform vec2 tileSize;

out vec2 TexCoord;

void main() {
    gl_Position = model * vec4(aPos, 0.0, 1.0);
    TexCoord = textureOffset + (aTexCoord * tileSize);
}