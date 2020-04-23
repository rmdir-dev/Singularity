//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

in vec4 vertColor;
in vec2 uvs;

void main() 
{
	outFragColor = vertColor;
}