#include<GL/glew.h>
#include<GL/glut.h>
#include "FrameBuffer.h"
#include "myModel.h"
#include "DataStructure.h"
#include "Camera.h"
#define WINWIDTH 800
#define WINHEIGHT 600
#define ZMIN -1000000

int winWidth = 800, winHeight = 600;
FrameBuffer fbuffer(winWidth, winHeight);	//颜色缓存
float polyZ;								//记录当前最大深度
glm::vec3 curColor;							//记录当前绘制的颜色
vector<PTNode *> pt[WINHEIGHT];				//分类多边形表
vector<ETNode *> et[WINHEIGHT];				//分类边表
vector<AETNode *> aet[WINHEIGHT];			//活化边表
vector<IPLNode *> ipl[WINHEIGHT];			//活化多边形表
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		//相机
myModel m_model("model/cat.obj");
enum {Out, In};
int gl_ymin = 1000000, gl_ymax = -10000000;		//全局的最值
vector<Polygen> gl_polygen;
//glm::vec3 bgColor(1.0f, 0.f, 0.f);		//背景色
glm::vec3 bgColor(0.5f, 0.5f, 0.5f);

bool cmp(glm::vec3 &p1, glm::vec3 &p2)
{
	return p1[1] > p2[1];
	
}

bool cmp1(glm::vec3 &p1, glm::vec3 & p2)
{
	return p1[2] > p2[2];
}

//多当前活化边表按照交点x大小进行排序
bool cmp2(AETNode* p1, AETNode* p2)
{
	return p1->x < p2->x;
}

void preprocess()
{
	//FILE *fp = NULL;
	//fp = fopen("gl_polygen.txt", "w+");
	for (int i = 0; i < m_model.polygen.size(); i++)
	{
		Polygen tmp;
		tmp = m_model.polygen[i];

		float xmin, xmax, ymin, ymax;
		float spanx, spany;
		xmin = m_model.m_xmin;
		xmax = m_model.m_xmax;
		ymin = m_model.m_ymin;
		ymax = m_model.m_ymax;
		spanx = xmax - xmin;
		spany = ymax - ymin;
		float offsetX, offsetY;
		//offsetX = winWidth / 2.0f - spanx / 2.0f;
		//offsetY = winHeight / 2.0f - spany / 2.0f;
		offsetX = winWidth / 2.0f - (xmax + xmin) / 2.0f;
		offsetY = winHeight / 2.0f - (ymax + ymin) / 2.0f;
		float scaleFactor;
		scaleFactor = (float)winHeight / spany * (1.f / 2.f);

		glm::mat4 mtranslate, mscale, mview, mprojection;
		mtranslate = glm::translate(mtranslate, glm::vec3(offsetX, offsetY, 0.0f));
		mscale = glm::scale(mscale, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
		mprojection = glm::perspective(camera.Zoom, (float)winWidth / (float)winHeight, 0.1f, 100.0f);
		mview = camera.GetViewMatrix();
		glm::vec3 pos1 = tmp.p1;
		glm::vec4 pos1Trans = /*mscale * mprojection * mview * */mtranslate * glm::vec4(pos1, 1.0f);
		pos1[0] = pos1Trans[0];
		pos1[1] = pos1Trans[1];
		pos1[2] = pos1Trans[2];

		glm::vec3 pos2 = tmp.p2;
		glm::vec4 pos2Trans =  /** mscale *mprojection * mview **/ mtranslate * glm::vec4(pos2, 1.0f);
		pos2[0] = pos2Trans[0];
		pos2[1] = pos2Trans[1];
		pos2[2] = pos2Trans[2];

		glm::vec3 pos3 = tmp.p3;
		glm::vec4 pos3Trans = /*mprojection * mview * */mtranslate * glm::vec4(pos3, 1.0f);
		pos3[0] = pos3Trans[0];
		pos3[1] = pos3Trans[1];
		pos3[2] = pos3Trans[2];

		Polygen newPolygen;
		newPolygen.a = tmp.a;
		newPolygen.b = tmp.b;
		newPolygen.c = tmp.c;
		newPolygen.d = tmp.d;
		glm::vec3 normal = glm::cross(pos2 - pos1, pos3 - pos2);
		normal = glm::normalize(normal);
		float costheta = glm::dot(normal, glm::vec3(0.0f, 0.0f, 1.0f));
		newPolygen.color = glm::vec3(abs(costheta), abs(costheta), abs(costheta));
		//fprintf(fp, "%.2f %.2f %.2f\n", newPolygen.color[0], newPolygen.color[1], newPolygen.color[2]);
		newPolygen.p1 = pos1;
		newPolygen.p2 = pos2;
		newPolygen.p3 = pos3;
		gl_polygen.push_back(newPolygen);
	}
	//fclose(fp);
	//fp = NULL;
}

void maxY(glm::vec3 point[3])
{
	sort(point, point + 3, cmp);
}

void maxZ(glm::vec3 point[3])
{
	sort(point, point + 3, cmp1);
}

//清空活化多边形表和活化边表
void clear()
{
	for (int i = 0; i < winHeight; i++)
	{
		for (int j = 0; j < aet[i].size(); j++)
		{
			if (aet[i][j] != NULL)
			{
				free(aet[i][j]);
				aet[i][j] = NULL;
			}
		}
		aet[i].clear();
	}
	
	for (int i = 0; i < winHeight; i++)
	{
		for (int j = 0; j < ipl[i].size(); j++)
		{
			if (ipl[i][j] != NULL)
			{
				free(ipl[i][j]);
				ipl[i][j] = NULL;
			}
		}
		ipl[i].clear();
	}

	for (int i = 0; i < winHeight; i++)
	{
		for (int j = 0; j < pt[i].size(); j++)
		{
			if (pt[i][j] != NULL)
			{
				free(pt[i][j]);
				pt[i][j] = NULL;
			}
		}
		pt[i].clear();
	}
	for (int i = 0; i < winHeight; i++)
	{
		for (int j = 0; j < et[i].size(); j++)
		{
			if (et[i][j] != NULL)
			{
				free(et[i][j]);
				pt[i][j] = NULL;
			}

		}
		et[i].clear();
	}
}

//创建分类多边形表和分类边表
//注意排除一些ymax<0的多边形
void contructPTAndET()
{
	for (int i = 0; i < gl_polygen.size(); i++)
	{
		//printf("%d\n", i);
		Polygen polygen = gl_polygen[i];
		glm::vec3 point[3];
		point[0] = polygen.p1;
		point[1] = polygen.p2;
		point[2] = polygen.p3;
		maxY(point);	//对三个点按照y值大小进行降序排序

		float tmpminx = 10000.0f, tmpmaxx = -10000.0f;
		float tmpminy = 10000.0f, tmpmaxy = -10000.0f;
		for (int k = 0; k < 3; k++)
		{
			if (point[k][0] > tmpmaxx) tmpmaxx = point[k][0];
			if (point[k][0] < tmpminx) tmpminx = point[k][0];
			if (point[k][1] > tmpmaxy) tmpmaxy = point[k][1];
			if (point[k][1] < tmpminy) tmpminy = point[k][1];
		}
		if (point[0][1] <= 0.0f || point[0][0] <= 0.0f || point[0][1] >= winHeight - 1 || point[0][0] >= winWidth - 1 || (tmpmaxx - tmpminx) <= 2 || (tmpmaxy - tmpminy) <= 2) continue;		//对ymax < 0的多边形不进行处理

		int ymax;		//ymax的取整值
		ymax = (int)(point[0][1] + 0.5f);
		int ysecond;
		ysecond = point[1][1] < 0.0f ? (int)0 : (int)(point[1][1] + 0.5);	//这里将位于y = 0以下的点都设定为0
		ysecond = ysecond > winHeight - 1 ? winHeight - 1 : ysecond;
		int ythird;
		ythird = point[2][1] < 0.0f ? (int)0 : (int)(point[2][1] + 0.5);
		ythird = ythird > winHeight - 1 ? winHeight - 1: ythird;
		if (ymax > gl_ymax) gl_ymax = ymax;
		if (ymax < gl_ymin) gl_ymin = ymax;

		//创建分类多边形节点
		PTNode *node = (PTNode *)malloc(sizeof(PTNode));
		node->ymax = ymax;			//这里暂时有个疑问，存储的值需要是整数吗?
		node->polyID = i;
		node->a = polygen.a;
		node->b = polygen.b;
		node->c = polygen.c;
		node->d = polygen.d;
		node->deltaY = ymax - ythird;		//多边形行跨越的扫描线数目
		node->color = polygen.color;
		node->flag = -1;					//进/出标志
		///
		glm::vec3 pointZ[3];
		pointZ[0] = point[0];
		pointZ[1] = point[1];
		pointZ[2] = point[2];
		maxZ(pointZ);
		node->z = point[0][2];
		///
		pt[ymax].push_back(node);


		//边一
		ETNode *etNode = (ETNode *)malloc(sizeof(ETNode));
		etNode->polyID = i;
		etNode->deltaY = ymax - ysecond;			
		etNode->ymax = ymax;
		etNode->x = point[0][0] < 0.0f ? 0.0f : point[0][0];
		etNode->z = point[0][2];		//记录顶点深度
		etNode->mark = false;			//初始化边使用标志
		glm::vec3 tmp = point[0] - point[1];
		if (abs(tmp[0]) < 1.0f) etNode->deltaX = 0.0f;		//注意
		else if (abs(tmp[1]) >= 1.0f)
		{
			etNode->deltaX = -tmp[0] / tmp[2];
			et[ymax].push_back(etNode);	
		}
		//else etNode->deltaX = -tmp[0] / tmp[1];		//这里没有考虑水平的情况，水平不加边

		//边二
		ETNode *etNode1 = (ETNode *)malloc(sizeof(ETNode));
		etNode1->polyID = i;
		etNode1->deltaY = ymax - ythird;
		etNode1->ymax = ymax;
		etNode1->x = point[0][0] < 0.0f ? 0.0f : point[0][0];
		etNode1->z = point[0][2];		//
		etNode1->mark = false;
		glm::vec3 tmp1 = point[0] - point[2];
		if (tmp1[0] < 0.000001f) etNode1->deltaX = 0.0f;
		else etNode1->deltaX = -tmp1[0] / tmp1[1];
		et[ymax].push_back(etNode1);

		//边三
		ETNode *etNode2 = (ETNode *)malloc(sizeof(ETNode));
		etNode2->polyID = i;
		etNode2->ymax = ysecond;
		etNode2->x = point[1][0] < 0.0f ? 0.0f : point[1][0];
		etNode2->deltaY = ysecond - ythird;
		etNode2->z = point[1][2];		///
		etNode2->mark = false;
		glm::vec3 e3 = point[1] - point[2];
		if (e3[0] < 0.00001f) etNode2->deltaX = 0.0f;
		else etNode2->deltaX = -e3[0] / e3[1];
		et[ysecond].push_back(etNode2);
		//printf("%d\n", i);
		

	}
	printf("finish constructPTAndEt\n");
}

int findEdge(int polyID, int y)
{
	for (int i = 0; i < et[y].size(); i++)
	{
		if (et[y][i]->polyID == polyID && !et[y][i]->mark) return i;
	}
	return -1; //没有找到
}

//添加新的活化边,加入左右边
void addAETNode(int y, int polyID)
{
	//printf("addAETNode:%d\n", y);
	//printf("et_size:%d\n", et[y].size());
	//for (int i = 0; i < et[y].size(); i++)
	//{
	//printf("node:%d:", i);
	int indexL, indexR;
	indexL = findEdge(polyID, y);
	et[y][indexL]->mark = true;		//标志已经被加入活化边表中
	indexR = findEdge(polyID, y);
	et[y][indexR]->mark = true;
	ETNode *etnodel = et[y][indexL];
	ETNode *etnoder = et[y][indexR];

	//把左边加入活化边表中
	AETNode* newNodeL = (AETNode *)malloc(sizeof(AETNode));
	newNodeL->polyID = etnodel->polyID;
	newNodeL->x = etnodel->x;
	newNodeL->dx = etnodel->deltaX;
	newNodeL->dy = etnodel->deltaY;
	newNodeL->z = etnodel->z;
	float a, b, c;
	a = gl_polygen[etnodel->polyID].a;
	b = gl_polygen[etnodel->polyID].b;
	c = gl_polygen[etnodel->polyID].c;
	if (c == 0)			//面在水平面上
	{
		newNodeL->dzx = 0.0f;
		newNodeL->dzy = 0.0f;
	}
	else
	{
		newNodeL->dzx = -a / c;
		newNodeL->dzy = b / c;
	}
	aet[y].push_back(newNodeL);


	//加入右边
	AETNode* newNodeR = (AETNode*)malloc(sizeof(AETNode));
	newNodeR->polyID = etnoder->polyID;
	newNodeR->x = etnoder->x;
	newNodeR->dx = etnoder->deltaX;
	newNodeR->dy = etnoder->deltaY;
	newNodeR->z = etnoder->z;
	float ar, br, cr;
	ar = m_model.polygen[etnoder->polyID].a;
	br = m_model.polygen[etnoder->polyID].b;
	cr = m_model.polygen[etnoder->polyID].c;
	if (cr == 0)
	{
		newNodeR->dzx = 0.0f;
		newNodeR->dzy = 0.0f;
	}
	else
	{
		newNodeR->dzx = -a / c;
		newNodeR->dzy = b / c;
	}
	aet[y].push_back(newNodeR);
	//}
}


//创建y扫描线对应的活化多边形表项和活化边表项
void createIPLAndAETTerm(int y)
{
	for (int i = 0; i < pt[y].size(); i++)
	{
		PTNode *tmp_ptnode = pt[y][i];
		IPLNode *newIplnode = (IPLNode*)malloc(sizeof(IPLNode));
		newIplnode->polyID = tmp_ptnode->polyID;
		newIplnode->a = tmp_ptnode->a;
		newIplnode->b = tmp_ptnode->b;
		newIplnode->c = tmp_ptnode->c;
		newIplnode->d = tmp_ptnode->d;
		newIplnode->deltaY = tmp_ptnode->deltaY;		//初始剩余扫描线数
		newIplnode->color = tmp_ptnode->color;
		newIplnode->flag = -1;
		newIplnode->z = tmp_ptnode->z;
		ipl[y].push_back(newIplnode);
		addAETNode(y, tmp_ptnode->polyID);	//如果有新的多边形加入到活化多边形表中，则添加新边到活化边表中
	}
}

int findPoly(int y, int ID)
{
	for (int i = 0; i < ipl[y].size(); i++)
	{
		if (ID == ipl[y][i]->polyID) return i;
	}
	return -1;		//暂时不考虑没有边返回的情况
}


int judgeColor(int y)
{
	float zmax = -10000.0f;
	int index = -1;
	for (int i = 0; i < ipl[y].size(); i++)
	{
		if (ipl[y][i]->flag == 1 && ipl[y][i]->z > zmax) {
			index = i;
			zmax = ipl[y][i]->z;
		}
	}
	return index;
}

void drawScaneLine2(int y)
{
	if (aet[y].size() == 0) return;
	sort(&aet[y][0], &aet[y][0] + aet[y].size(), cmp2);
	AETNode *e1 = aet[y][0];
	int indexL = findPoly(y, e1->polyID);
	ipl[y][indexL]->flag *= -1;
	for (int i = 1; i < aet[y].size(); i++)
	{
		AETNode *e2 = aet[y][i];
		int indexR = findPoly(y, e2->polyID);
		int colorIndex = judgeColor(y);
		if (colorIndex == -1) curColor = bgColor;
		else
		{
			curColor = ipl[y][colorIndex]->color;
			//printf("%.2f %.2f %.2f\n", curColor[0], curColor[1], curColor[2]);
		}
		int startI = (int)(e1->x + 0.5f);
		int endI = (int)(e2->x + 0.5f);
		endI = endI > winWidth - 1 ? winWidth - 1 : endI;
		for (int j = startI; j <= endI; j++)
		{
			fbuffer.setPixel(j, y, curColor);
		}

		ipl[y][indexR]->flag *= -1;
		e1 = e2;

	}

}
void drawScaneLine3(int y)
{
	if (aet[y].size() == 0) return;
	int count = 0;
	int  curZ = ZMIN;
	sort(&aet[y][0], &aet[y][0] + aet[y].size(), cmp2);
	AETNode *e1 = aet[y][0];
	int indexL = findPoly(y, e1->polyID);
	ipl[y][indexL]->flag *= -1;
	int flagL = ipl[y][indexL]->flag;
	count++;
	for (int i = 1; i < aet[y].size(); i++)
	{
		AETNode *e2 = aet[y][i];
		int indexR = findPoly(y, e2->polyID);
		ipl[y][indexR]->flag *= -1;
		int flagR = ipl[y][indexR]->flag;
		count++;
		if (flagL == 1 && flagR == 1)
		{
			if (e1->z > polyZ)
			{
				curColor = ipl[y][indexL]->color;
				polyZ = e1->z;
				//printf("1 1\n");
			}

		}
		else if (flagL == -1 && flagR == 1)
		{
			//if (count % 2 == 0)
			//{
			//	curColor = bgColor;
			//	polyZ = ZMIN;
			//	//curColor = glm::vec3(0.0f, 0.0f, 0.0f);
			//	//printf("-1 1\n");
			//}
			int colorIndex = judgeColor(y);
			if (colorIndex == -1)
			{
				curColor = bgColor;
				polyZ = ZMIN;
			}
			else
			{
				curColor = ipl[y][colorIndex]->color;

			}

		}
		else if (flagL == 1 && flagR == -1)
		{
			if (e1->z <= e2->z && e2->z > polyZ)
			{
				polyZ = e2->z;
				curColor = ipl[y][indexR]->color;
			}
			else if (e1->z > e2->z && e1->z > polyZ)
			{
				polyZ = e1->z;
				curColor = ipl[y][indexL]->color;
			}
			//printf("1 -1\n");
		}
		else
		{
			if (e2->z > polyZ)
			{
				polyZ = e2->z;
				curColor = ipl[y][indexR]->color;
				//printf("-1 -1\n");
			}
		}
		int startI = (int)(e1->x + 0.5);
		int end = (int)(e2->x + 0.5);
		//int startI = (int)(e1->x);
		//int end = (int)(e2->x);
		end = end > winWidth - 1 ? winWidth - 1 : end;
		for (int j = startI; j <= end; j++)
		{
			fbuffer.setPixel(j, y, curColor);
			//printf("%.2f %.2f %.2f\n", curColor[0], curColor[1], curColor[2]);
			//printf("%.2f %.2f %.2f\n", (fbuffer.getPixelAddress(j, y))->x, fbuffer.getPixelAddress(j, y)->y, fbuffer.getPixelAddress(j, y)->z);
		}
		e1 = e2;
		flagL = flagR;
		indexL = indexR;
	}
}
void drawScaneLine1(int y)
{
	if (aet[y].size() == 0) return;
	int count = 0;
	int  curZ = ZMIN;
	sort(&aet[y][0], &aet[y][0] + aet[y].size(), cmp2);
	AETNode *e1 = aet[y][0];
	int indexL = findPoly(y, e1->polyID);
	ipl[y][indexL]->flag *= -1;
	int flagL = ipl[y][indexL]->flag;
	count++;
	for (int i = 1; i < aet[y].size(); i++)
	{
		AETNode *e2 = aet[y][i];
		int indexR = findPoly(y, e2->polyID);
		//ipl[y][indexR]->flag *= -1;
		int flagR = ipl[y][indexR]->flag;
		flagR = ipl[y][indexR]->flag * (-1);
		count++;
		if (flagL == 1 && flagR == 1)
		{
			if (e1->z > polyZ)
			{
				curColor = ipl[y][indexL]->color;
				polyZ = e1->z;
				//printf("1 1\n");
			}

		}
		else if (flagL == -1 && flagR == 1)
		{
			if (count % 2 == 1)
			{
				curColor = bgColor;
				polyZ = ZMIN;
				curColor = glm::vec3(0.0f, 0.0f, 0.0f);
				printf("-1 1\n");
			}
			//int colorIndex = judgeColor(y);
			//if (colorIndex == -1)
			//{
			//	//curColor = bgColor;
			//	curColor = glm::vec3(0.0f, 0.0f, 1.0f);
			//	polyZ = ZMIN;
			//}
			//else
			//{
			//	curColor = ipl[y][colorIndex]->color;
			//	
			//}
			
		}
		else if (flagL == 1 && flagR == -1)
		{
			if (e1->z <= e2->z && e2->z > polyZ)
			{
				polyZ = e2->z;
				curColor = ipl[y][indexR]->color;
			}
			else if (e1->z > e2->z && e1->z > polyZ)
			{
				polyZ = e1->z;
				curColor = ipl[y][indexL]->color;
			}
			//printf("1 -1\n");
		}
		else
		{
			if (e2->z > polyZ)
			{
				polyZ = e2->z;
				curColor = ipl[y][indexR]->color;
				//printf("-1 -1\n");
			}
		}
		int startI = (int)(e1->x + 0.5);
		int end = (int)(e2->x + 0.5);
		//int startI = (int)(e1->x);
		//int end = (int)(e2->x);
		end = end > winWidth - 1 ? winWidth - 1 : end;
		for (int j = startI; j <= end; j++)
		{
			fbuffer.setPixel(j, y, curColor);
			//printf("%.2f %.2f %.2f\n", curColor[0], curColor[1], curColor[2]);
			//printf("%.2f %.2f %.2f\n", (fbuffer.getPixelAddress(j, y))->x, fbuffer.getPixelAddress(j, y)->y, fbuffer.getPixelAddress(j, y)->z);
		}
		ipl[y][indexR]->flag *= -1;
		e1 = e2;
		flagL = flagR;
		indexL = indexR;
	}
}

//绘制扫描线
//void drawScaneLine(int y)
//{
//	glm::vec3 colorL, colorR;
//	if (aet[y].size() == 0) return;
//	sort(&aet[y][0], &aet[y][0] + aet[y].size(), cmp2);
//	AETNode *e1 = aet[y][0];
//	int index = findPoly(y, e1->polyID);
//	if (index == -1) return;		//应该不会存在找不到的情况吧？
//	ipl[y][index]->flag *= -1;		//这里保留意见，到底是在ipl中查找还是在pt中查找
//	int flagE1 = ipl[y][index]->flag;
//	colorL = ipl[y][index]->color;
//	int count = 0;
//	count++;
//	for (int i = 1; i < aet[y].size(); i++)
//	{
//		AETNode *e2 = aet[y][i];
//		int e2Index = findPoly(y, e2->polyID);
//		ipl[y][e2Index]->flag *= -1;
//		int flagE2 = ipl[y][e2Index]->flag;
//		colorR = ipl[y][e2Index]->color;
//		if (flagE2 == 1) count++;
//		if (flagE1 == 1 && flagE2 == 1)		//同时进入，则当前区间取e1对应的多边形的颜色
//		{
//			int i = e1->x < 0 ? (int)(e1->x - 0.5) : (int)(e1->x + 0.5);
//			int end = e2->x < 0 ? (int)(e2->x - 0.5) : (int)(e2->x + 0.5);
//			curColor = colorL;
//			while (i <= end)
//			{
//				fbuffer.setPixel(i, y, curColor);
//				i++;
//			}
//			if(e1->z > curZ) curZ = e1->z;			//记录当前深度
//		}
//		else if(flagE1 == 1 && flagE2 == -1)		//进->出需要比较深度，相对复杂
//		{
//			if (e1->z < e2->z)		
//			{
//				if (e2->z > curZ)	//改变颜色需要交点的深度大于当前记录的深度
//				{
//					curZ = e2->z;
//					curColor = colorR;
//				}
//			}
//			else
//			{
//				if (e1->z > curZ)
//				{
//					curColor = colorL;
//					curZ = e1->z;
//				}
//			}
//			int i = e1->x < 0 ? (int)(e1->x - 0.5) : (int)(e1->x + 0.5);
//			int end = e2->x < 0 ? (int)(e2->x - 0.5) : (int)(e2->x + 0.5);
//			while (i <= end)
//			{
//				fbuffer.setPixel(i, y, curColor);
//				i++;
//			}
//		}
//		else if (flagE1 == -1 && flagE2 == 1) //出->进，背景色
//		{
//			//curColor = ipl[y][e2Index]->color;
//			curColor = bgColor;
//			curZ = e2->z;
//			int i = e1->x < 0 ? (int)(e1->x - 0.5) : (int)(e1->x + 0.5);
//			int end = e2->x < 0 ? (int)(e2->x - 0.5) : (int)(e2->x + 0.5);
//			while (i <= end)
//			{
//				fbuffer.setPixel(i, y, curColor);
//				i++;
//			}
//		}
//		else
//		{
//			curColor = ipl[y][e2Index]->color;
//			int i = e1->x < 0.0f ? (int)(e1->x - 0.5f) : (int)(e1->x + 0.5f);
//			int end = e2->x < 0.0f ? (int)(e2->x - 0.5f) : (int)(e2->x + 0.5f);
//			while (i <= end)
//			{
//				fbuffer.setPixel(i, y, curColor);
//				i++;
//			}
//			if (e2->z > curZ) curZ = e2->z;
//		}
//		e1 = e2;
//	}
//
//}

void updateAET(int y)
{
	//printf("size:%d\n", aet[y].size());
	for (int i = 0; i < aet[y].size(); i++)
	{
		//printf("%d\n", i);
		AETNode *curNode = aet[y][i];
		if (curNode->dy > 0)
		{
			AETNode *newNode = (AETNode *)malloc(sizeof(AETNode));
			newNode->polyID = curNode->polyID;
			newNode->x = curNode->x + curNode->dx;
			newNode->dx = curNode->dx;
			newNode->dy = curNode->dy - 1;
			newNode->z = curNode->z + curNode->dzx * (curNode->dx) + curNode->dzy;
			newNode->dzx = curNode ->dzx;
			newNode->dzy = curNode->dzy;
			aet[y - 1].push_back(newNode);
		}
		else
		{
			int index = findEdge(curNode->polyID, y - 1);
			if (index != -1)
			{
				ETNode *curNode = et[y - 1][index];
				AETNode *newNode = (AETNode *)malloc(sizeof(AETNode));
				newNode->polyID = curNode->polyID;
				newNode->x = curNode->x;
				newNode->dx = curNode->deltaX;
				newNode->dy = curNode->deltaY;
				newNode->z = curNode->z;
				float a, b, c;
				a = gl_polygen[curNode->polyID].a;
				b = gl_polygen[curNode->polyID].b;
				c = gl_polygen[curNode->polyID].c;
				if (c == 0)
				{
					newNode->dzx = 0;
					newNode->dzy = 0;
				}
				else
				{
					newNode->dzx = -a / c;
					newNode->dzy = b / c;
				}
				aet[y - 1].push_back(newNode);
			}

		}
		free(curNode);
		curNode = NULL;
	}
	aet[y].clear();
}

void updateIPL(int y)
{
	for (int i = 0; i < ipl[y].size(); i++)
	{
		IPLNode *curNode = ipl[y][i];
		if (curNode->deltaY > 0)
		{
			IPLNode *newNode = (IPLNode *)malloc(sizeof(IPLNode));
			newNode->deltaY = curNode->deltaY - 1;
			newNode->a = curNode->a;
			newNode->b = curNode->b;
			newNode->c = curNode->c;
			newNode->d = curNode->d;
			newNode->polyID = curNode->polyID;
			newNode->flag = -1;
			newNode->z = curNode->z;
			newNode->color = curNode->color;
			ipl[y - 1].push_back(newNode);
		}
		free(curNode);	//释放本行的表项
	}
	ipl[y].clear();
}

//区间扫描线算法
void spanScanLineZBuffer()
{
	clear();
	contructPTAndET();
	//clearAETAndIPL();
	printf("gl_ymax:%d gl_ymin:%d\n", gl_ymax, gl_ymin);
	for (int y = gl_ymax; y >= gl_ymin; y--)
	{
		createIPLAndAETTerm(y);
		//FILE *fp = NULL;
		//fp = fopen("gl_ymax.txt", "w+");
		//for (int i = 0; i < aet[gl_ymax].size(); i++)
		//{
		//	//fprintf(fp, "%d ", et[gl_ymax][i]->ymax);
		//	//fprintf(fp, "%d ", et[gl_ymax][i]->polyID);
		//	//fprintf(fp, "%d ", et[gl_ymax][i]->deltaY);
		//	//fprintf(fp, "%.2f ", et[gl_ymax][i]->deltaX);
		//	//fprintf(fp, "%.2f ", et[gl_ymax][i]->x);
		//	//fprintf(fp, "%.2f ", et[gl_ymax][i]->z);
		//	//fprintf(fp, "%d\n", et[gl_ymax][i]->mark);
		//	fprintf(fp, "%d ", aet[gl_ymax][i]->polyID);
		//	fprintf(fp, "%d ", aet[gl_ymax][i]->dy);
		//	fprintf(fp, "%.2f ", aet[gl_ymax][i]->x);
		//	fprintf(fp, "%.2f ", aet[gl_ymax][i]->z);
		//	fprintf(fp, "%.2f ", aet[gl_ymax][i]->dx);
		//	fprintf(fp, "%.2f ", aet[gl_ymax][i]->dzx);
		//	fprintf(fp, "%.2f\n", aet[gl_ymax][i]->dzy);
		//}
		//fclose(fp);
		//fp = NULL;
		//for (int k = 0; k < ipl[y].size(); k++)
		//{
		//	printf("ID:%d flag:%d\n", ipl[y][k]->polyID, ipl[y][k]->flag);
		//}
		drawScaneLine1(y);
		//if (y == 226)
		//{
		//	FILE *fp = NULL;
		//	fp = fopen("model/aet_mid.txt", "w+");
		//	for (int k = 0; k < aet[y].size(); k++)
		//	{
		//		fprintf(fp, "%d ", aet[y][k]->polyID);
		//		fprintf(fp, "%.2f ", aet[y][k]->z);
		//		fprintf(fp, "%d ", aet[y][k]->dy);
		//		fprintf(fp, "%.2f ", aet[y][k]->dx);
		//		fprintf(fp, "%.2f ", aet[y][k]->dzx);
		//		fprintf(fp, "%.2f ", aet[y][k]->dzy);
		//		fprintf(fp, "%.2f\n", aet[y][k]->x);
		//	}
		//	fclose(fp);
		//	fp = fopen("model/ipl_mid.txt", "w+");
		//	for (int k = 0; k < ipl[y].size(); k++)
		//	{
		//		fprintf(fp, "%d ", ipl[y][k]->polyID);
		//		fprintf(fp, "%.2f ", ipl[y][k]->z);
		//		fprintf(fp, "%d ", ipl[y][k]->deltaY);
		//		fprintf(fp, "%d ", ipl[y][k]->flag);
		//		fprintf(fp, "%.2f %.2f %.2f\n", ipl[y][k]->color[0], ipl[y][k]->color[1], ipl[y][k]->color[2]);
		//	}
		//	fclose(fp);
		//	fp = fopen("model/fbuffer.txt", "w+");
		//	for (int k = 0; k < winWidth; k++)
		//	{
		//		fprintf(fp, "%.2f %.2f %.2f\n", fbuffer.getPixelAddress(k, y)->x, fbuffer.getPixelAddress(k, y)->y, fbuffer.getPixelAddress(k, y)->z);
		//	}
		//	fclose(fp);
		//}
		updateAET(y);
		updateIPL(y);
		printf("finish %d line\n", y);
	}
	printf("finish drawLines\n");
}

void init()
{
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winWidth - 1, 0, winHeight - 1);
	//gluPerspective(camera.Zoom, (float)winWidth / (float)winHeight, 1.5f, 20.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	polyZ = ZMIN;
	curColor = bgColor;
	fbuffer.resizeBuffer(winWidth, winHeight);
	fbuffer.init(bgColor);
}

void disply()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	fbuffer.init(bgColor);
	preprocess();
	spanScanLineZBuffer();
	glRasterPos2i(0, 0);
	//FILE *fp;
	//fp = fopen("fbuffer.txt", "w+");
	//for (int i = 0; i < winHeight; i++)
	//{
	//	for (int j = 0; j < winWidth; j++)
	//	{
	//		fprintf(fp, "%.2f %.2f %.2f\n", fbuffer.getPixelAddress(j, i)[0], fbuffer.getPixelAddress(j, i)[0], fbuffer.getPixelAddress(j, i)[0]);
	//	}
	//}
	//fclose(fp);
	//fp = NULL;
	glDrawPixels(winWidth, winHeight, GL_RGB, GL_FLOAT, fbuffer.getPixelAddress(0, 0));
	glutSwapBuffers();
}

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(camera.Zoom, (double)winWidth / (double)winHeight, 1.5f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	winWidth = width;
	winHeight = height;
	//clear();
	init();
	//disply();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("span-scanLine-zbuffer");
	init();
	glutDisplayFunc(disply);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}



//
//
////#include<GL/glew.h>
////#include<GLFW/glfw3.h>
////#include<iostream>
////#include"FrameBuffer.h"
////#include"Triple.h"
////
////enum {Color, NumRenderBuffers};
////GLuint framebuffer, renderbuffers[NumRenderBuffers];
////
////int main()
////{
////	glfwInit();
////	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
////	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
////	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
////
////	GLFWwindow* window;
////	window = glfwCreateWindow(800, 600, "hello glDrawPixel", nullptr, nullptr);
////	if (window == nullptr)
////	{
////		std::cerr << "Fail to create the window" << std::endl;
////		return -1;
////	}
////	glfwMakeContextCurrent(window);
////	if (glewInit() != GLEW_OK)
////	{
////		std::cerr << "Fail to init glew" << std::endl;
////		return -1;
////	}
////	int width, height;
////	glfwGetFramebufferSize(window, &width, &height);
////	glViewport(0, 0, width, height);
////	//glfwSetKeyCallback(window, key_callback);
////	//glClearColor(1.0, 1.0, 1.0, 1.0);
////
////	/*glGenRenderbuffers(NumRenderBuffers, renderbuffers);
////	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffers[Color]);
////	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, 256, 256);
////	
////	glGenFramebuffers(1, &framebuffer);
////	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
////
////	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffers[Color]);
////*/
////	FrameBuffer fbuffer(width, height);
////	fbuffer.init();
////	for (int hI = 0; hI < height; hI++)
////	{
////		for (int wI = 0; wI < width; wI++)
////		{
////			//Eigen::Vector3d color(0.2, 0.3,	0.4);
////			Triple color;
////			color.x = 128;
////			color.y = 128;
////			color.z = 128;
////			fbuffer.setPixel(wI, hI, color);
////			//std::cout << *fbuffer.getPixel(0, 0) << std::endl;
////
////		}
////
////	}
////	Triple *t = fbuffer.getPixel(0, 0);
////	//glClearColor(0., 0., 0., 1.);
////	while (!glfwWindowShouldClose(window))
////	{
////		glfwPollEvents();
////		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
////		//glViewport(0, 0, width, height);
////		//glClearColor(1.f, 1.f, 1.f, 1.f);	
////		glClear(GL_COLOR_BUFFER_BIT);
////		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
////		
////		//glRasterPos2i(0, 0);
////		glReadPixels(0, 0, fbuffer.getFrameBufferWidth(), fbuffer.getFrameBufferHeight(), GL_RGB, GL_UNSIGNED_BYTE, fbuffer.getPixel(0, 0));
////		//glDrawPixels(fbuffer.getFrameBufferWidth(), fbuffer.getFrameBufferHeight(), GL_RGB, GL_UNSIGNED_BYTE, fbuffer.getPixel(0, 0));
////		glfwSwapBuffers(window);
////	}
////	glfwTerminate();
////	return 0;
////	
////}

//#include<GL/glew.h>
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//#include<iostream>
//#include"Camera.h"
//
//
//Camera camera(glm::vec3(0., 0., 3.));
//int width = 900;
//int height = 600;
//int main()
//{
//	glm::vec3 original = glm::vec3(10., 10., 10.);
//	std::cout << original[0] << "," << original[1] << "," << original[2]  << std::endl;
//
//	glm::mat4 projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 100.f);
//	glm::mat4 proOrth = glm::ortho(0.f, 900.f, 0.f, 600.f);
//	//glm::mat4 transform = glm::translate(transform, glm::vec3(0.0f, -1.75f, 0.0f));
//	//transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));
//	//glm::mat4 view = camera.GetViewMatrix();
//	//glm::vec4 res = projection * view * transform * glm::vec4(original, 1.0f);
//	glm::vec4 res = projection * glm::vec4(original, 1.0f);
//	
//	std::cout << res[0] << "," << res[1] << "," << res[2] << "," << res[3] << std::endl;
//	std::cout << res[0] / res[3] << "," << res[1] / res[3] << "," << res[3] << std::endl;
//	system("pause");
//	return 0;
//}