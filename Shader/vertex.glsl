#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 camMatrix;

out vec2 TexCoord;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = camMatrix * model * vec4(aPos,1.0);
}