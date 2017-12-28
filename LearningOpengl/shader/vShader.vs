#version 440 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragPosition;
out vec2 texcoord;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1.0f);
	fragPosition = vec3(model * vec4(vPosition, 1.0f));
	normal = vNormal;
	texcoord = vTexcoord;
}