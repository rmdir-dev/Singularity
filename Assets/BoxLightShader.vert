//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;

uniform vec3 inColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertColor;

void main()
{
    vertColor = vec4(inColor, 1.0);
    gl_Position = projection * view * model * vec4(inPos, 1.0);
}