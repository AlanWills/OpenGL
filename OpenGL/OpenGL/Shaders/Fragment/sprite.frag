#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColour;

void main()
{    
    color = spriteColour * texture(image, TexCoords);
}