#version 440 core

in vec3 outColor;
in vec2 outTexcoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform float mixParameter;

out vec4 color;

void main()
{
	
	color = mix( texture(Texture0, outTexcoord), texture( Texture1, vec2(outTexcoord.x, 1.0f - outTexcoord.y) ) * vec4(outColor, 1.0), mixParameter);	
}