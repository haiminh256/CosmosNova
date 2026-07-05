
#version 460 core

in vec4 Color;
in vec2 TexCoord;

uniform sampler2D tex0;
layout (location = 0) out vec4 FragColor;

void main()
{
    FragColor = texture(tex0, TexCoord) * Color;   
} 