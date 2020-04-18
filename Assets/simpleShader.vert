//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;

uniform vec3 color;

out vec3 vertColor;

void main()
{
    vertColor = color;
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
}