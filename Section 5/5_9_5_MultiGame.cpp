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
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();


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
	unsigned int num = 0;
	while (cin >> num)
	{
		unsigned int cur = 1;
		unsigned int last = 1;
		int count = 1;
		bool overFlow = false;
		while (cur < num)
		{
			last = cur;
			// 如果是奇数，说明是第一个人
			if (count & 1)
			{
				cur *= 9;
			}
			else
			{
				cur *= 2;
			}
			if (last > cur)
			{
				// 溢出了
				overFlow = true;
				break;
			}
			++count;
		}
		if (overFlow)
		{
			cout << "Stan wins." << endl;
		}
		else
		{
			if (count & 1)
			{
				cout << "Ollie wins." << endl;
			}
			else
			{
				cout << "Stan wins." << endl;
			}
		}
	}
}
