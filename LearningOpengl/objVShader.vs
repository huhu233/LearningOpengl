#version 440 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPosition;
out vec3 normal;

void main()
{

	gl_Position = projection * view * model * vec4(vPosition, 1.0f);
	fragPosition = vec3( model * vec4(vPosition, 1.0f) );

	normal = vNormal;
}