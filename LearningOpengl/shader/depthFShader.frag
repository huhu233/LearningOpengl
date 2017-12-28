#version 440 core
in vec2 outTexcoord;

uniform sampler2D texture0;
out vec4 color;

void main()
{
	//color = vec4(texture(texture0, outTexcoord));
	color = vec4(vec3(gl_FragCoord.z), 1.0f);
}