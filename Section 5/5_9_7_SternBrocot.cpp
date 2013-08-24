#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	����
*/
string Calculate(unsigned num1, unsigned num2);

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

	ofstream fout;
	fout.open(outputStr.c_str());

	cout.rdbuf(fout.rdbuf());
#endif

	Process();
			
}

void Process()
{
	unsigned int num1, num2;
	while (cin >> num1 >> num2)
	{
		if (num1 == 1 && num2 == 1)
		{
			break;
		}
		cout << Calculate(num1, num2) << endl;
	}

}

string Calculate(unsigned m, unsigned n)
{
	string str;
	if (m == 1 && n == 1)
	{
		return "I";
	}
	int leftUp = 0;
	int leftDown = 1;
	int rightUp = 1;
	int rightDown = 0;

	int middleUp = leftUp + rightUp;
	int middleDown = leftDown + rightDown;
	double fnum = (double)m / n;

	while (!(middleUp == m && middleDown == n))
	{
		double fmiddle = (double)middleUp / middleDown;
		if (fnum < fmiddle)
		{
			str.append(1, 'L');
			rightUp = middleUp;
			rightDown = middleDown;
		}
		else if (fnum > fmiddle)
		{
			str.append(1, 'R');
			leftUp = middleUp;
			leftDown = middleDown;
		}				
		middleUp = leftUp + rightUp;
		middleDown = leftDown + rightDown;
	}

	return str;
}