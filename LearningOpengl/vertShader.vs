#version 440 core

in vec2 Texcoords;
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNomal;
layout(location = 2) in vec2 vTexcoord;

out vec2 texcoords;

void main()
{
	gl_Position = vPosition;
}