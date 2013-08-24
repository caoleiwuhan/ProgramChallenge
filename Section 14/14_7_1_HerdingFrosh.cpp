#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>
#include <hash_map>


using namespace std;

#define _MY_DEBUG_

// 容差值
const double EPSILON = 1e-7;

// 点的最大数目
const int MAXV = 1001;

// 多边形中最大的顶点数
const int MAXPOLY = 1001;

// 维度：2维
const int DIMENSION = 2;

struct Point
{
	double x;
	double y;
	Point()
	{
		x = 0.0;
		y = 0.0;
	}

	Point(double _x, double _y) : x(_x), y(_y) {}

	bool operator == (const Point &p)
	{
		return ((x == p.x) && (y == p.y));
	}

	bool operator != (const Point &p)
	{
		return (!(*this == p));
	}


};

struct Polygon
{
	int n;
	Point points[MAXPOLY];

	Polygon()
	{
		n = 0;
	}

	Polygon(int _n)
	{
		n = _n;
	}
	
};


// 点坐标
double pos[MAXV][2];

// 点集
Point in[MAXV];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	测试凸包生成程序	
*/
void TestConvexHull();


// 第一个点
Point firstPoint;

/*
	计算凸包的结果
	in：入点
	n: 点的个数
	hull：凸包

	对于in：入点的要求，不能有重复的点
*/
void ConvexHull(Point in[], int n, Polygon * hull);

/*
	复制点
*/
void CopyPoint(Point &from, Point & to);

/*
	对入点排序，并删除重复点
	并改变点的个数
*/
void SortAndRemoveDuplicates(Point in[], int &n);

/*
	对点进行排序：以leftlower为小
	即：靠左，且靠下
	p1 < p2	:-1
	p1 = p2 : 0
	p1 > p2 : 1
*/
int LeftLowerPointCmp(const void *p1, const void *p2);

/*
	对点进行排序：以到第一个点的逆时针角为依据
*/
int SmallAnglePointCmp(const void *p1, const void *p2);

/*
	判断三点是否共线
*/
bool ColLinear(const Point &p1, const Point &p2, const Point &p3);

/*
	计算三点形成的面积：有符号的
*/
double SignedTriangleArea(const Point &p1, const Point &p2, const Point &p3);

/*
	计算两点之间的距离
*/
double DistanceTwoPoint(const Point &p1, const Point &p2);

/*
	ccw:p3是否在（p1,p2)的逆时针方向上
*/
bool ClockClockWise(const Point &p1, const Point &p2, const Point &p3);
	
/*
	cw:p3是否在（p1,p2)的顺时针方向上
*/
bool ClockWise(const Point &p1, const Point &p2, const Point &p3);

/*
	CrossProduct
*/
double CrossProduct( const Point &a, const Point &b, const Point &c );



/*
	打印点数据
*/
void PrintPoints(Point in[], int n);

/*	
	大于Polygon
*/	
void PrintPolygon(const Polygon &p);



int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{

#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*
	ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());
	*/

#endif

	//Process();
	TestConvexHull();
}


void TestConvexHull()
{
	int num = 0;
	double x, y;
	cin >> num;
	for (int i = 0; i < num; ++i)
	{
		cin >> x >> y;
		in[i].x = x;
		in[i].y = y;
	}
	// 计算凸包
	Polygon poly;
	ConvexHull(in, num, &poly);

	// 打印凸包
	PrintPolygon(poly);

}


void Process()
{
	int count = 0;
	cin >> count;
	
	while (count--)
	{
		// 每一组数据的个数
		int num = 0;
		cin >> num;
		// 加上（0,0）一共（num+1)个
		++num;

		pos[0][0] = 0;
		pos[0][1] = 0;

		for (int i = 1; i < num; ++i)
		{
			cin >> pos[i][0] >> pos[i][1];


		}

	}


	if (count)
	{
		cout << endl;
	}

}



void ConvexHull(Point in[], int n, Polygon * hull)
{
	// 当前凸包的点数
	int top = 0;
	// 如果入点<=3，则所有入点都是凸包
	if (n <= 3)
	{
		for (int i = 0; i < n; ++i)
		{
			CopyPoint(in[i], hull->points[i]);
		}
		hull->n = n;
		return;
	}

	SortAndRemoveDuplicates(in, n);

// 打印
PrintPoints(in, n);


	CopyPoint(in[0], firstPoint);

	qsort(in + 1, n - 1, sizeof(Point), SmallAnglePointCmp);

cout << endl;
PrintPoints(in, n);
cout << endl;

	// 第一个点是凸包的一个顶点，放入hull中
	CopyPoint(firstPoint, hull->points[0]);

	// 把第二个点也放入，以方便形成三角形
	CopyPoint(in[1], hull->points[1]);

	// 把第一个点放入最后，作为哨兵
	CopyPoint(firstPoint, hull->points[n]);
	
	// 当前hull中的凸包的最上面的索引
	top = 1;
	// 从第二个开始开始处理（其实是第三个）
	int i = 2;

	while (i < n)
	{		
		//if (CrossProduct(hull->points[top-1], hull->points[top], in[i]) <= 0)
		while ((top > 0) && (!ClockClockWise(hull->points[top-1], hull->points[top], in[i])))
		{
			--top;
		}
		++top;
		CopyPoint(in[i], hull->points[top]);
		++i;
	}

	hull->n = top + 1;
}

void CopyPoint(Point &from, Point & to)
{
	to.x = from.x;
	to.y = from.y;
}

void SortAndRemoveDuplicates(Point in[], int &n)
{
	if (n <= 1)
	{
		return;
	}
	// 原来的点数
	int oldNum = n;
	// 索引值
	int newIndex = 0;
	qsort(in, n, sizeof(Point), LeftLowerPointCmp);

	for (int i = 1; i < oldNum; ++i)
	{
		if (in[newIndex] != in[i])
		{
			CopyPoint(in[i], in[++newIndex]);
		}		
	}
	n = newIndex + 1;
}


int LeftLowerPointCmp(const void *pLeft, const void *pRight)
{
	Point p1(((Point *)pLeft)->x, ((Point *)pLeft)->y);
	Point p2(((Point *)pRight)->x, ((Point *)pRight)->y);

	/*if (p1.x != p2.x)
	{
		if (p1.x < p2.x)
		{
			return (-1);
		}
		return (1);
	}
	if (p1.y < p2.y)
	{
		return (-1);
	}
	if (p1.y > p2.y)
	{
		return (1);
	}*/

	if (p1.y != p2.y)
	{
		if (p1.y < p2.y)
		{
			return (-1);
		}
		return (1);
	}
	if (p1.x < p2.x)
	{
		return (-1);
	}
	if (p1.x > p2.x)
	{
		return (1);
	}

	return (0);
}

int SmallAnglePointCmp(const void *pLeft, const void *pRight)
{
	Point p1(((Point *)pLeft)->x, ((Point *)pLeft)->y);
	Point p2(((Point *)pRight)->x, ((Point *)pRight)->y);

	if (ColLinear(firstPoint, p1, p2))
	{
		if (DistanceTwoPoint(firstPoint, p1) <= DistanceTwoPoint(firstPoint, p2))
		{
			return (-1);
		}
		return (1);
	}
	if (ClockClockWise(firstPoint, p1, p2))
	{
		return (-1);
	}
	return (1);
}

bool ColLinear(const Point &p1, const Point &p2, const Point &p3)
{
	return (fabs(SignedTriangleArea(p1, p2, p3)) < EPSILON);
}

double SignedTriangleArea(const Point &p1, const Point &p2, const Point &p3)
{
	return( (p1.x * p2.y - p1.y * p2.x + p1.y * p3.x 
		- p1.x * p3.y + p2.x * p3.y - p3.x * p2.y) / 2.0);
}

double DistanceTwoPoint(const Point &p1, const Point &p2)
{
	return ( sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p2.y - p2.y)) );
}

bool ClockClockWise(const Point &p1, const Point &p2, const Point &p3)
{
	return (SignedTriangleArea(p1, p2, p3) > EPSILON);
}

bool ClockWise(const Point &p1, const Point &p2, const Point &p3)
{
	return (SignedTriangleArea(p1, p2, p3) < -EPSILON);
}



void PrintPoints(Point in[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << '(' << in[i].x << ',' << in[i].y << ')' << endl;
	}
}

void PrintPolygon(const Polygon &poly)
{
	int num = poly.n;
	for (int i = 0; i < num; ++i)
	{
		cout << '(' << poly.points[i].x << ',' << poly.points[i].y << ')' << endl;
	}
}


double CrossProduct( const Point &a, const Point &b, const Point &c )
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}