#pragma once
#include<gl/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>
using namespace std;
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	
	Mesh(vector<Vertex> vertices, vector<GLuint> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}

};