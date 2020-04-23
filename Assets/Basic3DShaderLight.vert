//Shader VERTEX
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUvs;
layout (location = 3) in vec3 inNormals;

struct Material 
{
	vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float opacity;
    float shininess;
};

uniform Material material;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 vColor;

//Will be removed;
uniform vec3 lightPosition;

out vec4 vertColor;
out vec2 uvs;
out vec3 normals;

void main()
{
    uvs = inUvs;
    vertColor = material.ambient;
    normals = inNormals;
    gl_Position = projection * view * model * vec4(inPos, 1.0);
}