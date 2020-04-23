//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUvs;
layout (location = 3) in vec3 inNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 vColor;

out vec4 vertColor;
out vec2 uvs;
out vec3 normals;
out vec3 fragPosition;

void main()
{
    uvs = inUvs;
    normals = mat3(transpose(inverse(model))) * inNormals;;
    fragPosition = vec3(model * vec4(inPos, 1.0));
    gl_Position = projection * view * vec4(fragPosition, 1.0);
}