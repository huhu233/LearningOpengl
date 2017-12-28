#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<string>
struct Vertex
{
	glm::vec3 Positions;
	glm::vec3 Normals;
	glm::vec3 Texcoords;
};

struct Texture
{
	GLuint type;
	std::string name;
};

