#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

//�������α�ڵ�
struct PTNode
{
	int ymax;		//���������yֵ
	int polyID;		//����εı��
	float a;
	float b;
	float c;
	float d;
	int deltaY;	//���Խ��ɨ���ߵ�����
	glm::vec3 color;	//����ε���ɫ
	int flag;		//in:1 / out: -1
	float z;		//�ö�����ȵ����Ǹö���ε���ȣ�������ȵ������ԣ���ʱ�������ʷֵ�����
	//PTNode *next;		//��vector���������������ָ����ʱ����
};

//����߱�ڵ�
struct ETNode
{
	int ymax;		
	GLuint polyID;
	float x;			//�϶����x����
	float z;			//�϶�������
	float deltaX;		//��������ɨ���߽����x�����
	int deltaY;			//�߿�Խ��ɨ������Ŀ
	bool mark;			//��־�Ƿ�����߱���,��Ѱ����һ����ʱ��Ҫ�õ�
	//ETNode *next;		//
};

struct IPLNode
{
	int polyID;
	float a;
	float b;
	float c;
	float d;
	int deltaY;		//�����ʣ���ɨ������Ŀ
	glm::vec3 color;
	int flag;
	float z;
	//IPLNode *next;	
};


//���ͶӰ����α߽���ɨ�����ཻ�ı�
struct AETNode
{
	GLuint polyID;		//�������ڵĶ���εı��
	GLfloat x;			//ɨ������ߵĽ���
	GLfloat dx;			//����ɨ���߽���x����֮��
	GLint dy;			//ʣ���ཻ��ɨ������Ŀ
	GLfloat z;			//���㴦�����
	GLfloat dzx;		//��ɨ����������\�ƹ�һ������ʱ�����������ƽ���������, -a/c
	GLfloat dzy;		//��y���������ƹ�һ��ɨ����ʱ,���������ƽ����������, b/c

	//GLfloat xl;		//�󽻵��x����
	//GLfloat dxl;		//(�󽻵����)������ɨ���߽����x����֮��
	//GLfloat dyl;		//�Ժ��󽻵����ڱ��ཻ��ɨ������Ϊ��ֵ���Ժ�����ÿ����һ��ɨ����-1
	//GLfloat xr;	
	//GLfloat dxr;
	//GLfloat dyr;
	//GLfloat zl;			//�󽻵㴦���������ƽ������ֵ
	//GLfloat zr;			//�ҽ��㴦���������ƽ������ֵ
	//IPLNode *next;
};

