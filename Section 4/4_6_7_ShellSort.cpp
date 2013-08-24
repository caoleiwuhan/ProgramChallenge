#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <cassert>
#include <iomanip>
#include <map>

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


int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/1.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);
	//cout.rdbuf(fout.rdbuf());

#endif

	Process();
		
}

void Process()
{
	// 测试数据组数
	int count = 0;
	cin >> count;
	while (count--)
	{
		map<string, int> inputMap;
		map<int, string> outputMap;
		// shell数目
		int num = 0;
		cin >> num;
		// 去掉换行符
		cin.get();

		for (int i = 0; i < num; ++i)
		{
			string name;
			getline(cin, name);
			inputMap[name] = i;
		}
		// 从0到num-1
		for (int i = 0; i < num; ++i)
		{
			string name;
			getline(cin, name);
			outputMap[i] = name;
		}
		int last = inputMap[outputMap[num - 1]];
		int index = -1;
		for (int i = num - 2; i >= 0; --i)
		{
			string name = outputMap[i];
			int curIndex = inputMap[name];
			if (curIndex > last)
			{
				index = i;
				break;
			}
			else
			{
				last = curIndex;
			}
		}
		bool needEndl = false;
		for (int i = index; i >= 0; --i)
		{
			cout << outputMap[i] << endl;
			needEndl = true;
		}
		if (!needEndl)
		{
			cout << endl;
		}

		if (count/* && needEndl*/)
		{
			cout << endl;
		}
	}
}

