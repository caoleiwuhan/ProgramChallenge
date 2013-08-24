#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

#define _MY_DEBUG_

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	����
*/
void Handle(unsigned marbleNum, unsigned c1, unsigned n1, unsigned c2, unsigned n2);

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
	unsigned marbleNum = 0;
	unsigned c1 = 0;
	unsigned n1 = 0;
	unsigned c2 = 0;
	unsigned n2 = 0;
	while (cin >> marbleNum)
	{
		if (marbleNum == 0)
		{
			break;
		}
		cin >> c1 >> n1;
		cin >> c2 >> n2;
		Handle(marbleNum, c1, n1, c2, n2);
	}

}

void Handle(unsigned marbleNum, unsigned c1, unsigned n1, unsigned c2, unsigned n2)
{
	// ���
	unsigned best1 = 0;
	unsigned best2 = 0;
	// c1����
	unsigned num1 = 0;
	// c2����
	unsigned num2 = 0;
	// ����
	unsigned min = 0xFFFFFFFF;
	// c1�ܸ���
	unsigned total1 = 0;
	while (total1 <= marbleNum)
	{
		num2 = (marbleNum - total1) / n2;
		// ����ܱ�����
		if (num2 * n2 == marbleNum - total1)
		{
			unsigned curBest = num1 * c1 + num2 * c2;
			if (curBest < min)
			{
				min = curBest;
				best1 = num1;
				best2 = num2;
			}
		}
		++num1;
		total1 += n1;
	}

	if (min == 0xFFFFFFFF)
	{
		cout << "failed" << endl;
	}
	else
	{
		cout << best1 << ' ' << best2 << endl;
	}
}