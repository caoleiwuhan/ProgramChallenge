#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//#define _MY_DEBUG_

// 距离Vector
int numbers[510];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

int GetDistance(int medium, int numCount);

/*
	测试输入
*/
void Test();


int main()
{
	MainStructure();
	return 0;
}

void Test()
{
	int num;
	while (cin >> num)
	{
		cout << num << endl;
	}
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

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
#endif

//	Test();
	Process();
		
}

void Process()
{
	// 测试数据的组数
	int count;
	cin >> count;
	while (count--)
	{
		int numCount = 0;
		cin >> numCount;
		for (int i = 0; i < numCount; ++i)
		{
			cin >> numbers[i];
		}
		sort(numbers, numbers + numCount);
		int medium = 0;
		if (numCount & 1)
		{
			medium = numbers[numCount / 2];
		}
		else
		{
			medium = (numbers[numCount / 2] + numbers[numCount / 2 - 1]) / 2;
		}
		
		cout << GetDistance(medium, numCount) << endl;
	}
}

int GetDistance(int medium, int numCount)
{
	int total = 0;
	for (int i = 0; i < numCount; ++i)
	{
		total += abs(numbers[i] - medium);
	}
	return total;
}
