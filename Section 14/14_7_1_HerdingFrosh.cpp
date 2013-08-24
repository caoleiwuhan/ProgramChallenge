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

// �ݲ�ֵ
const double EPSILON = 1e-7;

// ��������Ŀ
const int MAXV = 1001;

// ����������Ķ�����
const int MAXPOLY = 1001;

// ά�ȣ�2ά
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


// ������
double pos[MAXV][2];

// �㼯
Point in[MAXV];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	����͹�����ɳ���	
*/
void TestConvexHull();


// ��һ����
Point firstPoint;

/*
	����͹���Ľ��
	in�����
	n: ��ĸ���
	hull��͹��

	����in������Ҫ�󣬲������ظ��ĵ�
*/
void ConvexHull(Point in[], int n, Polygon * hull);

/*
	���Ƶ�
*/
void CopyPoint(Point &from, Point & to);

/*
	��������򣬲�ɾ���ظ���
	���ı��ĸ���
*/
void SortAndRemoveDuplicates(Point in[], int &n);

/*
	�Ե����������leftlowerΪС
	���������ҿ���
	p1 < p2	:-1
	p1 = p2 : 0
	p1 > p2 : 1
*/
int LeftLowerPointCmp(const void *p1, const void *p2);

/*
	�Ե���������Ե���һ�������ʱ���Ϊ����
*/
int SmallAnglePointCmp(const void *p1, const void *p2);

/*
	�ж������Ƿ���
*/
bool ColLinear(const Point &p1, const Point &p2, const Point &p3);

/*
	���������γɵ�������з��ŵ�
*/
double SignedTriangleArea(const Point &p1, const Point &p2, const Point &p3);

/*
	��������֮��ľ���
*/
double DistanceTwoPoint(const Point &p1, const Point &p2);

/*
	ccw:p3�Ƿ��ڣ�p1,p2)����ʱ�뷽����
*/
bool ClockClockWise(const Point &p1, const Point &p2, const Point &p3);
	
/*
	cw:p3�Ƿ��ڣ�p1,p2)��˳ʱ�뷽����
*/
bool ClockWise(const Point &p1, const Point &p2, const Point &p3);

/*
	CrossProduct
*/
double CrossProduct( const Point &a, const Point &b, const Point &c );



/*
	��ӡ������
*/
void PrintPoints(Point in[], int n);

/*	
	����Polygon
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
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
	// ����͹��
	Polygon poly;
	ConvexHull(in, num, &poly);

	// ��ӡ͹��
	PrintPolygon(poly);

}


void Process()
{
	int count = 0;
	cin >> count;
	
	while (count--)
	{
		// ÿһ�����ݵĸ���
		int num = 0;
		cin >> num;
		// ���ϣ�0,0��һ����num+1)��
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
	// ��ǰ͹���ĵ���
	int top = 0;
	// ������<=3����������㶼��͹��
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

// ��ӡ
PrintPoints(in, n);


	CopyPoint(in[0], firstPoint);

	qsort(in + 1, n - 1, sizeof(Point), SmallAnglePointCmp);

cout << endl;
PrintPoints(in, n);
cout << endl;

	// ��һ������͹����һ�����㣬����hull��
	CopyPoint(firstPoint, hull->points[0]);

	// �ѵڶ�����Ҳ���룬�Է����γ�������
	CopyPoint(in[1], hull->points[1]);

	// �ѵ�һ������������Ϊ�ڱ�
	CopyPoint(firstPoint, hull->points[n]);
	
	// ��ǰhull�е�͹���������������
	top = 1;
	// �ӵڶ�����ʼ��ʼ������ʵ�ǵ�������
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
	// ԭ���ĵ���
	int oldNum = n;
	// ����ֵ
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