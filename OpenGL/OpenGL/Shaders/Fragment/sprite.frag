#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform vec4 objectColour;
uniform sampler2D objectTexture;

void main()
{
    color = objectColour * texture(objectTexture, TexCoord);
}