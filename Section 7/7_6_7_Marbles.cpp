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
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	计算
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
	// 结果
	unsigned best1 = 0;
	unsigned best2 = 0;
	// c1个数
	unsigned num1 = 0;
	// c2个数
	unsigned num2 = 0;
	// 花费
	unsigned min = 0xFFFFFFFF;
	// c1总个数
	unsigned total1 = 0;
	while (total1 <= marbleNum)
	{
		num2 = (marbleNum - total1) / n2;
		// 如果能被整除
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