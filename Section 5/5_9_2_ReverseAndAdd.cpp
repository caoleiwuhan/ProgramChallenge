#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
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
	判断一个数是否是回文
*/
bool IsHuiWan(unsigned int num);

/*
	将一个数翻转
*/
unsigned int ReverseNum(unsigned int num);

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
	int count = 0;
	unsigned int num = 0;
	cin >> count;
	while (count--)
	{
		cin >> num;
		int ans = 0;
		while (!IsHuiWan(num))
		{
			// 将num翻转
			unsigned int rNum = ReverseNum(num);
			num += rNum;
			++ans;
		}
		cout << ans << " " << num << endl;
	}
}



bool IsHuiWan(unsigned int num)
{
	// 1.考虑将num转化成str
	int numArr[20];
	int count = 0;
	while (num > 0)
	{
		numArr[count++] = num % 10;
		num /= 10;
	}
	// 判断是否是回文数
	for (int i = 0; i < count / 2; ++i)
	{
		if (numArr[i] != numArr[count - 1 - i])
		{
			return false;
		}
	}

	return true;
}

unsigned int ReverseNum(unsigned int num)
{
	int numArr[20];
	int count = 0;
	while (num > 0)
	{
		numArr[count++] = num % 10;
		num /= 10;
	}
	unsigned rNum = 0;
	for (int i = 0; i < count; ++i)
	{
		rNum = numArr[i] + rNum * 10;			
	}
	return rNum;
}