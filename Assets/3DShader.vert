//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUvs;
layout (location = 3) in vec3 inNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertColor;
out vec2 uvs;

void main()
{
    uvs = inUvs;
    vertColor = inColor;
    gl_Position = projection * view * model * vec4(inPos, 1.0);
}