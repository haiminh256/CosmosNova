#version 460 core

layout(location = 0) in vec3 aPosition;
<<<<<<< HEAD
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoord;
=======
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
>>>>>>> origin

out vec4 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * model * vec4(aPosition, 1.0);
    Color = aColor;
    TexCoord = aTexCoord;
}