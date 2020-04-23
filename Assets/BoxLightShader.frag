//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

in vec4 vertColor;

void main() 
{
	outFragColor = vertColor;
}