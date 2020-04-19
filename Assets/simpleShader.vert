//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUvs;

//uniform vec3 color;

out vec4 vertColor;
out vec2 uvs;

void main()
{
    uvs = inUvs;
    vertColor = inColor;
    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
}