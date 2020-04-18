//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

in vec3 vertColor;

void main() 
{
	outFragColor = vec4(vertColor, 1.0);
}