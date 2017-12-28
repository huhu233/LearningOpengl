#version 440 core

in vec2 texcoords;
uniform sampler2D texture_Diffuse1;
uniform sampler2D texture_Diffuse2;
uniform sampler2D texture_Diffuse3;
uniform sampler2D texture_Specular1;
uniform sampler2D texture_Specular2;

out vec4 color;

void main()
{
	color = texture(texture_Diffuse1, texcoords);
}