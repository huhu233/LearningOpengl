#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

//分类多边形表节点
struct PTNode
{
	int ymax;		//多边形最大的y值
	int polyID;		//多边形的编号
	float a;
	float b;
	float c;
	float d;
	int deltaY;	//表跨越的扫描线的数量
	glm::vec3 color;	//多边形的颜色
	int flag;		//in:1 / out: -1
	float z;		//用顶点深度当成是该多边形的深度，利用深度的连贯性，暂时不考虑剖分的问题
	//PTNode *next;		//用vector代替链表，所以这个指针暂时不用
};

//分类边表节点
struct ETNode
{
	int ymax;		
	GLuint polyID;
	float x;			//上定点的x坐标
	float z;			//上顶点的深度
	float deltaX;		//相邻两条扫描线交点的x坐标差
	int deltaY;			//边跨越的扫描线数目
	bool mark;			//标志是否加入活化边表中,在寻找下一条边时需要用到
	//ETNode *next;		//
};

struct IPLNode
{
	int polyID;
	float a;
	float b;
	float c;
	float d;
	int deltaY;		//多边形剩余的扫描线数目
	glm::vec3 color;
	int flag;
	float z;
	//IPLNode *next;	
};


//存放投影多边形边界与扫描线相交的边
struct AETNode
{
	GLuint polyID;		//交点所在的多边形的编号
	GLfloat x;			//扫描线与边的交点
	GLfloat dx;			//相邻扫描线交点x坐标之差
	GLint dy;			//剩余相交的扫描线数目
	GLfloat z;			//交点处的深度
	GLfloat dzx;		//沿扫描线向右做\移过一个像素时，多边形所在平面深度增量, -a/c
	GLfloat dzy;		//沿y方向向下移过一根扫描线时,多边形所在平面的深度增量, b/c

	//GLfloat xl;		//左交点的x坐标
	//GLfloat dxl;		//(左交点边上)两相邻扫描线交点的x坐标之差
	//GLfloat dyl;		//以和左交点所在边相交的扫描线数为初值，以后向下每处理一条扫描线-1
	//GLfloat xr;	
	//GLfloat dxr;
	//GLfloat dyr;
	//GLfloat zl;			//左交点处多边形所在平面的深度值
	//GLfloat zr;			//右交点处多边形所在平面的深度值
	//IPLNode *next;
};

