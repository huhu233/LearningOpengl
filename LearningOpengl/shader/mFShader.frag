#version 440 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{   
	
   // color = vec4(texture(texture_diffuse1, TexCoords));
   color = vec4(0.2f, 0.3f, 0.4f, 1.0f);
}