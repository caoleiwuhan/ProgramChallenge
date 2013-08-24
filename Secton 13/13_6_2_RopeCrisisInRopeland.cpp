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



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	计算长度
*/
double CalRopeLen(double x1, double y1, double x2, double y2, double r);

double Dist(double x1, double y1, double x2, double y2);

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

	Process();

}
void Process()
{
	int count = 0;
	cin >> count;
	while (count--)
	{
		double x1, y1, x2, y2, r;
		cin >> x1 >> y1 >> x2 >> y2 >> r;


	}

}

double CalRopeLen(double x1, double y1, double x2, double y2, double r)
{
	if ((x1 >= r && x2 >= r) ||
		(x1 <= -r && x2 <= -r) ||
		(y1 >= r && y2 >= r) ||
		(y1 <= -r && y2 <= -r))
	{
		return Dist(x1, y1, x2, y2);
	}
	// 1.计算圆形（0,0）到两点之间的距离
	// 1.列出直线方程 : ax + by + c = 0
	double a, b, c;
	if (x1 == x2)
	{
		a = 1;
		b = 0;
		c = -x1;
	}
	else
	{
		b = 1;
		a = -(y1 - y2) / (x1 - x2);
		c = -(a * x1) - (b * y1);
	}
	// 计算单到直线的距离
	double dist = 0;
	if (a == 0 && b == 0)
	{
		dist = fabs(c);
	}
	else 
	{
		dist = fabs(c) / (sqrt(a * a + b * b));
	}
	if (dist >= r)
	{
		return Dist(x1, y1, x2, y2);
	}
	// 相交
	double d1x = Dist(x1, y1, 0, 0);
	double d1y = sqrt(d1x * d1x - r * r);

	double d2x = Dist(x2, y2, 0, 0);
	double d2y = sqrt(d2x * d2x - r * r);

	double d3 = Dist(x1, y1, x2, y2);

	double angle1 = acos((d1x * d1x + d2x * d2x - d3 * d3) / (2 * d1x * d2x));
	double angle2 = acos(r / d1x);
	double angle3 = acos(r / d2x);

	double diffAngle = angle1 - angle2 - angle3;
	double length = d1y + d2y + diffAngle * r;

	return length;
}

double Dist(double x1, double y1, double x2, double y2)
{
	return sqrt(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

/*
	计算叉积！！！
*/
