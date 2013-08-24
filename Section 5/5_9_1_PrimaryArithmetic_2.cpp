#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>

#include "HP.h"

using namespace std;

#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	传入两个非负整数，计算进位的数目
*/
int CarryCount(HP num1, HP num2);

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
	HP num1;
	HP num2;
	string str;

	while (true)
	{
		getline(cin, str);
		size_t pos = str.find(' ');
		string str1 = str.substr(0, pos);
		str = str.substr(pos + 1);
		num1 = str1;
		num2 = str;
		if (num1 == 0 && num2 == 0)
		{
			break;
		}
		int count = CarryCount(num1, num2);
		if (count == 0)
		{
			cout << "No carry operation." << endl;
		}
		else if (count > 1)
		{
			cout << count << " carry operations." << endl;
		}
		else
		{
			cout << count << " carry operation." << endl;
		}
	}
}

int CarryCount(HP num1, HP num2)
{
	// 进位次数
	int count = 0;
	// 进位
	HP carry;
	HP a;
	HP b;
	HP c;
	while (num1 > 0 || num2 > 0)
	{
		a = (num1 % 10);
		num1 /= 10;
		b = (num2 % 10);
		//num2 /= 10;
		//c = (a + b);
		//c += carry;

		//if (c > 9)
		//{
		//	++count;
		//}
		//carry = (c / 10);
	}
	return count;
}