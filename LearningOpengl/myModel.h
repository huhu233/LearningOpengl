#pragma once
#include<GL/glew.h>
#include<vector>
#include<string>
#include<iostream>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include "myMesh.h"
#include<cmath>
using namespace std;

struct Polygen
{
	float a;
	float b;
	float c;
	float d;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	//glm::vec3 normal;
	glm::vec3 color;
};
class myModel
{
public:
	vector<Polygen> polygen;
	float m_xmax;
	float m_xmin;
	float m_ymax;
	float m_ymin;
	myModel(GLchar *path)
	{
		m_xmax = -10000.0f;
		m_xmin = 10000.0f;
		m_ymax = -10000.0f;
		m_ymin = 10000.0f;
		this->loadModel(path);
		this->processPolygen();
	}


private:
	vector<Mesh> meshes;
	//vector<Polygen> polygen;
	string directory;
	//texture

	void loadModel(string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			 cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			 return;
		}
		this->directory = path.substr(0, path.find_last_of('/'));
		this->processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode* node, const aiScene* scene)
	{
		for (GLuint  i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<GLuint> indices;

		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 v;

			//read position
			v.x = mesh->mVertices[i].x;
			v.y = mesh->mVertices[i].y;
			v.z = mesh->mVertices[i].z;
			vertex.Position = v;
			if (v[0] < m_xmin) m_xmin = v[0];
			if (v[0] > m_xmax) m_xmax = v[0];
			if (v[1] < m_ymin) m_ymin = v[1];
			if (v[1] > m_ymax) m_ymax = v[1];
			//read normal
			//v.x = mesh->mNormals[i].x;
			//v.y = mesh->mNormals[i].y;
			//v.z = mesh->mNormals[i].z;
			//vertex.Normal = v;
			//read texture

			vertices.push_back(vertex);

		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}

	void processPolygen()
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			Mesh mesh = meshes[i];
			if (mesh.indices.size() < 3)
			{
				//printf("无法构成一个三角形\n");
				continue;
			}
			for (int j = 0; j < mesh.indices.size(); j += 3)
			{
				int p1I = mesh.indices[j];
				glm::vec3 p1 = mesh.vertices[p1I].Position;
				
				int p2I = mesh.indices[j + 1];
				glm::vec3 p2 = mesh.vertices[p2I].Position;
 
				int p3I = mesh.indices[j + 2];
				glm::vec3 p3 = mesh.vertices[p3I].Position;
				
				glm::vec3 normal = glm::cross(p2 - p1, p3 - p2);
				normal = glm::normalize(normal);
				float a = normal[0];
				float b = normal[1];
				float c = normal[2];
				float d = -(a * p1[0] + b * p1[1] + c * p1[2]);
				//颜色放到外面计算
				//if (normal[2] == 0) continue;		//垂直与xoy面的边不考虑
				//double costheta = glm::dot(normal, glm::vec3(0., 0., 1.)); //根据面法向量与001的夹角来设定多边形的颜色
				////glm::vec3 pColor = glm::vec3(abs(costheta * 0.5f + 0.5f), abs(costheta * 0.5 + 0.5f), abs(costheta * 0.5f + 0.5f));
				//glm::vec3 pColor;
				////if (costheta <= 0) pColor = glm::vec3(0., 0., 0);
				////else 
				//	pColor = glm::vec3(abs(costheta), abs(costheta), abs(costheta));
				Polygen poly;
				poly.a = a;
				poly.b = b;
				poly.c = c;
				poly.d = d;
				poly.p1 = p1;
				poly.p2 = p2;
				poly.p3 = p3;
				//poly.color = pColor;
				polygen.push_back(poly);
			}
		}
	}
};