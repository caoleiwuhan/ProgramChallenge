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

//#define _MY_DEBUG_

const int MAXV = 201;
// cake半径
const double CAKE_LENGTH = 50;

const double CHIP_RADIUS = 2.5;

const double EPSILON = 1e-7;
const double PI = acos(0.0) * 2.0;

// 点坐标
double pos[MAXV][2];


/*
MainStructure: 主结构
*/
void MainStructure();



/*
Process
*/
void Process();

int MaxPoint(int num);

/*
根据两点坐标和半径，求圆形坐标
返回值：
0：没有
1：一个
2：两个
*/
int Center(double x1, double y1, double x2, double y2, double radius, 
	double &cx1, double &cy1, double &cx2, double &cy2);

/*
两点之间距离
*/
double Distance(double x1, double y1, double x2, double y2);

/*
判断点是否在方形内
*/
bool IsPointInRec(double x, double y, double length);

/*
以x,y为圆形，有多少个
*/
int InCenterOfNum(double x, double y, int i, int j, int num);


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
	cin.ignore();

	string str;
	double pX, pY;
	while (count--)
	{
		cin.ignore();
		int index = 0;
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			stringstream ss(str);
			ss >> pX >> pY;
			pos[index][0] = pX;
			pos[index++][1] = pY;
		}
		int res = MaxPoint(index);
		if (res == 0)
		{
			res = 1;
		}

		if (index == 0)
		{
			res = 0;
		}
		cout << res << endl;

		if (count)
		{
			cout << endl;
		}
	}

}


int MaxPoint(int num)
{
	int res = 1;
	for (int i = 0; i < num - 1; ++i)
	{
		for (int j = i + 1; j < num; ++j)
		{
			double cx1, cy1, cx2, cy2;
			int ans = Center(pos[i][0], pos[i][1], pos[j][0], pos[j][1], CHIP_RADIUS,
				cx1, cy1, cx2, cy2);
			int tmp = 0;
			if (ans == 0)
			{
				continue;
			}
			if (ans == 1)
			{
				tmp = InCenterOfNum(cx1, cy1, i, j, num);
				if (tmp > res)
				{
					res = tmp;
				}
			}
			if (ans == 2)
			{
				tmp = InCenterOfNum(cx1, cy1, i, j, num);
				if (tmp > res)
				{
					res = tmp;
				}
				tmp = InCenterOfNum(cx2, cy2, i, j, num);
				if (tmp > res)
				{
					res = tmp;
				}
			}
		}
	}
	return res;
}


int Center(double x1, double y1, double x2, double y2, double radius, 
	double &cx1, double &cy1, double &cx2, double &cy2)
{
	double dist = Distance(x1, y1, x2, y2);
	// 如果距离大，没有
	if (dist > radius * 2.0)
	{
		return 0;
	}
	// 相等于半径,取两点的中心点
	if (fabs(dist - 2.0 * radius) < EPSILON)
	{
		cx1 = (x1 + x2) / 2.0;
		cy1 = (y1 + y2) / 2.0;
		return 1;
	}
	// 横纵坐标都不相同
	if (!((fabs(x1 - x2) < EPSILON) || (fabs(y1 - y2) < EPSILON)))
	{
		/*double delta = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2) - 2.0 * (y1 - y2)) / 
		(2.0 * (x1 - x2));
		double a = delta * delta + 1;
		double b = 2.0 * delta * x1 + 2.0 * y1;
		double c = x1 * x1 + y1 * y1 - radius * radius;

		double d = b * b - 4 * a * c;
		if (d < 0)
		{
		return 0;
		}
		if (fabs(a) < EPSILON)
		{
		return 0;
		}
		cy1 = ((-b) + sqrt(d)) / (2.0 * a);
		cx1 = delta * cy1;

		cy2 = ((-b) - sqrt(d)) / (2.0 * a);
		cy2 = delta * cy2;*/
		double MidpointX = (x1 + x2)/2.0;//中点X坐标
		double MidpointZ = (y1 + y2)/2.0;//中点Z坐标
		double TempI = (x1 - MidpointX)*(x1 - x2);
		double TempJ = (x1 - x2)*(x1 - x2);
		double TempK = radius*radius - y1*y1;
		double TempL = y1 - y2;
		double TempM = TempI - MidpointZ*TempL;
		double TempN = (TempL * TempL + TempJ)*(TempK*TempJ - TempM*TempM);
		double TempO = TempL*TempL + TempJ; 
		double TempP = TempM*TempL - y1*TempJ;
		cy1 = (sqrt((long double)((TempN + TempP*TempP)/(TempO*TempO)))) - (TempP/TempO);
		cx1 = MidpointX + ((y1 - y2) * (cy1 - MidpointZ))/(x2 - x1);
		cy2 = (-sqrt((long double)((TempN + TempP*TempP)/(TempO*TempO)))) - (TempP/TempO);
		cx2 = MidpointX + ((y1 - y2) * (cy2 - MidpointZ))/(x2 - x1);

double test1 = Distance(cx1, cy1, x1, y1);
double test2 = Distance(cx1, cy1, x2, y2);
double test3 = Distance(cx2, cy2, x1, y1);
double test4 = Distance(cx2, cy2, x2, y2);

		return 2;
	}
	else
	{
		// x相等或y相等
		if (fabs(x1 - x2) < EPSILON)
		{
			cy1 = (y1 + y2) / 2.0;
			cy2 = cy1;
			double tmp1 = radius * radius - (y1 - cy1) * (y1 - cy1);
			if (tmp1 < 0)
			{
				return 0;
			}
			if (fabs(tmp1) < EPSILON)
			{
				cy1 = x1;
				return 1;
			}
			double tmp2 = sqrt(tmp1);
			cx1 = x1 + tmp2;
			cx2 = x1 - tmp2;

			//double test1 = Distance(cx1, cy1, x1, y1);
			//double test2 = Distance(cx1, cy1, x2, y2);
			//double test3 = Distance(cx2, cy2, x1, y1);
			//double test4 = Distance(cx2, cy2, x2, y2);

			return 2;
		}
		if (fabs(y1 - y2) < EPSILON)
		{
			cx1 = (x1 + x2) / 2.0;
			cx2 = cx1;
			double tmp1 = radius * radius - (x1 - cx1) * (x1 - cx1);
			if (tmp1 < 0)
			{
				return 0;
			}
			if (fabs(tmp1) < EPSILON)
			{
				cx1 = y1;
				return 1;
			}
			double tmp2 = sqrt(tmp1);
			cy1 = y1 + tmp2;
			cy2 = y1 - tmp2;

			double test1 = Distance(cx1, cy1, x1, y1);
			double test2 = Distance(cx1, cy1, x2, y2);
			double test3 = Distance(cx2, cy2, x1, y1);
			double test4 = Distance(cx2, cy2, x2, y2);

			return 2;
		}
	}
}

double Distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

bool IsPointInRec(double x, double y, double length)
{
	if (x < 0 || x > length || y < 0 || y > length)
	{
		return false;
	}
	return true;
}

int InCenterOfNum(double x, double y, int i, int j, int num)
{
	int ans = 0;
	// 先判断交点是否出去了
	if (!IsPointInRec(x, y, CAKE_LENGTH))
	{
		return 0;
	}
	ans = 2;
	for (int k = 0; k < num; ++k)
	{
		if (k == i || k == j)
		{
			continue;
		}
		// 判断点的距离是否小于radius
		if (Distance(x, y, pos[k][0], pos[k][1]) < CHIP_RADIUS)
		{
			++ans;
		}
	}
	return ans;
}