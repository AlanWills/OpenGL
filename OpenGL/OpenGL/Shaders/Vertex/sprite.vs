#version 330 core

layout (location = 0) in vec4 positionTexCoords;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(positionTexCoords.xy, 0.0f, 1.0f);
	TexCoord = positionTexCoords.zw;
}