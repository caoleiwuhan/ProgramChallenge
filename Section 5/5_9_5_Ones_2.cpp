#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <stack>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Test 高精度结构
*/
void Test();

/*
	计算
*/
int CountNum(int num);


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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	
	

	cin.rdbuf(fin.rdbuf());	

	//ofstream fout;
	//fout.open(outputStr.c_str());

	//cout.rdbuf(fout.rdbuf());
#endif

	Process();
		
}


void Process()
{
	int num = 0;
	while (cin >> num)
	{		
		int count = CountNum(num);
		cout << count << endl;
	}
}


int CountNum(int hp)
{
	int count = 1;
	int num = 1;
	while (true)
	{
		int tmp = num % hp;
		// 如果能被整除
		if (tmp == 0)
		{
			return count;
		}
		// 否则增加num
		num *= 10;
		num += 1;
		num %= hp;

		++count;
	}
}