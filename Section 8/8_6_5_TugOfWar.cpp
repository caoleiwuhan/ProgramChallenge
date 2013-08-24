#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;

#define _MY_DEBUG_

// 所有人的体重
int weights[101];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	回溯法解决
	num: 一共多少个
	cur: 从当前位置开始
*/
void BackTrace(int num, int cur, int curWeight, int remainWeight, 
	int &best1, int &best2, int &bestAbs, int step);



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
	int count = 0;
	cin >> count;
	while (count--)
	{
		int totalWeight = 0;
		int tmp = 0;
		int num = 0;
		cin >> num;
		for (int i = 0; i < num; ++i)
		{
			cin >> tmp;
			weights[i] = tmp;
			totalWeight += tmp;
		}
		int best1 = 0;
		int best2 = totalWeight;
		int bestAbs = totalWeight;
		BackTrace(num, 0, 0, totalWeight, best1, best2, bestAbs, 0);
		if (best1 <= best2)
		{
			cout << best1 << ' ' << best2 << endl;
		}
		else
		{
			cout << best2 << ' ' << best1 << endl;
		}
		if (count)
		{
			cout << endl;
		}
	}
}

void BackTrace(int num, int cur, int curWeight, int remainWeight, 
	int &best1, int &best2, int &bestAbs, int step)
{
	// step 取小于等于num/2
	if (step == num / 2)
	{
		if (abs(curWeight - remainWeight) < bestAbs)
		{
			best1 = curWeight;
			best2 = remainWeight;
			bestAbs = abs(curWeight - remainWeight);
		}
		return;
	}
	if (step > num / 2)
	{
		return;
	}
	// step < num / 2
	for (int i = cur; i < num; ++i)
	{
		// 剪枝：如果大于abs，没有继续下去的必要
		if ((curWeight + weights[i]) - (remainWeight - weights[i]) > bestAbs)
		{
			continue;
		}
		BackTrace(num, i + 1, curWeight + weights[i], remainWeight - weights[i], 
			best1, best2, bestAbs, step + 1);
	}

}
