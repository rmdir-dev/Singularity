//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUvs;
layout (location = 3) in vec3 inNormals;
layout (location = 4) in vec3 inTangent;
layout (location = 5) in vec3 inBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 fragPosition = vec3(model * vec4(inPos, 1.0));
    gl_Position = projection * view * vec4(fragPosition, 1.0);
}