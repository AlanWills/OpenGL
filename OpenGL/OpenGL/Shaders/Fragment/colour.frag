#version 330 core

out vec4 color;

uniform vec4 objectColour;

void main()
{
    color = objectColour;
}