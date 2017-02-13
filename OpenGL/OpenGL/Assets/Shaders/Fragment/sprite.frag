#version 330 core
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D sprite;
uniform vec4 spriteColour;


void main()
{
	vec4 actualColour = spriteColour;
	color = actualColour * texture(sprite, TexCoord);
}