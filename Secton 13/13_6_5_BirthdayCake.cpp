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

const int MAXV = 101;

int pos[MAXV][2];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

bool IsLineOK(int num, int a, int b);

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
	int num = 0;
	while ((cin >> num) && (num != 0))
	{
		num *= 2;
		
		for (int i = 0; i < num; ++i)
		{
			cin >> pos[i][0] >> pos[i][1];
		}
		bool hasAnswer = false;
		for (int i = -500; (i <= 500) && !hasAnswer; ++i)
		{
			for (int j = -500; (j <= 500) && !hasAnswer; ++j)
			{
				if (i == 0 && j == 0)
				{
					continue;
				}
				if (IsLineOK(num, i, j))
				{
					cout << i << ' ' << j << endl;
					hasAnswer = true;
				}
			}
		}

	}
}

bool IsLineOK(int num, int a, int b)
{
	// a == 0 b == 0时特殊处理
	double denim = sqrt(double(a * a + b * b));

	int res = 0;
	for (int i = 0; i < num; ++i)
	{
		// 1.如果有樱桃在line上，不行
		int tmp = a * pos[i][0] + b * pos[i][1];
		if (tmp == 0)
		{
			return false;
		}
		if (tmp > 0)
		{
			++res;
		}
	}
	if (res * 2 == num)
	{
		return true;
	}
	return false;
}