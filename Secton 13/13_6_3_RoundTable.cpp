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

const double PI = 3.1415926;

const double EPSILON = 1e-6;


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	���㳤��
*/
double CalLen(double a, double b, double c);


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

	Process();

}
void Process()
{
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		stringstream ss(str);

		double a, b, c;
		ss >> a >> b >> c;
		double ans;
		if ((fabs(a) < EPSILON) || (fabs(b) < EPSILON) || (fabs(c) < EPSILON))
		{
			ans = 0;
		}
		else
		{
			double s = (a + b + c) / 2.000;
			ans = sqrt((s-a)*(s-b)*(s-c)/s);
			//ans = CalLen(a, b, c);
		}
		printf("The radius of the round table is: %.3lf\n", ans);
	}

}

double CalLen(double a, double b, double c)
{
	double angle1 = acos((a * a + b * b - c * c) / (2 * a * b));
	// ����0�Ȼ�180��
	if ((fabs(angle1) < EPSILON) || (fabs(angle1 - PI) < EPSILON))
	{
		return 0;
	}
	angle1 /= 2;

	double angle2 = acos((b * b + c * c - a * a) / (2 * b * c));
	// ����0�Ȼ�180��
	if ((fabs(angle2) < EPSILON) || (fabs(angle2 - PI / 2) < EPSILON))
	{
		return 0;
	}
	angle2 /= 2;

	double tmp = 1 / (tan(angle1)) + 1 / (tan(angle2));
	double ans = b / tmp;

	return ans;
}