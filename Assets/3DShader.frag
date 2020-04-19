//Shader FRAGMENT
#version 330 core

out vec4 outFragColor;

in vec4 vertColor;
in vec2 uvs;

uniform sampler2D texture0;

void main() 
{
	outFragColor = texture(texture0, uvs);
}