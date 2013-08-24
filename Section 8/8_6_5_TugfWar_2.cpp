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
#include <algorithm>

using namespace std;

//#define _MY_DEBUG_

const int MAX_WEIGHT = 45001;

// 
bool f[101][45100];
// 体重
int weights[101];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP(int num, int totalWeight);

/*
	如果相等:判断size个数之和是否能为halfWeight
*/
bool BackTrace(int num, int size, int halfWeight, int curWeight, int curNum, int step);

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
		// 排序
		sort(weights, weights + num);

		DP(num, totalWeight);
		int size = num / 2;
		int w1 = 0;
		int w2 = totalWeight;
		int wAbs = totalWeight;

		int halfTotalWeight = totalWeight / 2;
		for (int i = 0; i <= totalWeight; ++i)
		{
			if (f[size][i] && f[num - size][totalWeight - i])
			{
				// abs(i - (totalWeight - i)) = abs(i * 2 - totalWeight) = abs(i * 2 - tw)
				if (abs(i * 2 - totalWeight) < wAbs)
				{
					w1 = i;
					w2 = totalWeight - i;
					wAbs = abs(w1 - w2);
				}
			}
		}
		//// 如果w1 == w2:需要再算一遍
		//if (w1 == w2)
		//{
		//	if (BackTrace(num, num / 2, halfTotalWeight, 0, 0, 0))
		//	{
		//		cout << w1 << ' ' << w2 << endl;
		//	}
		//	else
		//	{ // w1 != w2
		//		w1 = 0;
		//		w2 = totalWeight;
		//		wAbs = totalWeight;
		//		for (int i = 0; i <= totalWeight; ++i)
		//		{
		//			if (f[size][i] && f[num - size][totalWeight - i] && (i * 2 != totalWeight))
		//			{						
		//				if (abs(i * 2 - totalWeight) < wAbs)
		//				{
		//					w1 = i;
		//					w2 = totalWeight - i;
		//					wAbs = abs(w1 - w2);
		//				}
		//			}
		//		}
		//		if (w1 < w2)
		//		{
		//			cout << w1 << ' ' << w2 << endl;
		//		}
		//		else
		//		{
		//			cout << w2 << ' ' << w1 << endl;
		//		}
		//	}
		//}
		//else
		{
			if (w1 < w2)
			{
				cout << w1 << ' ' << w2 << endl;
			}
			else
			{
				cout << w2 << ' ' << w1 << endl;
			}
		}

		if (count)
		{
			cout << endl;
		}
	}
}

void DP(int num, int totalWeight)
{
	memset(f, 0, sizeof(f));

	f[0][0] = true;
	int halfNum = num / 2;
	for (int i = 0; i <= halfNum; ++i)
	{
		for (int j = 0; j <= totalWeight; ++j)
		{
			if (f[i][j])
			{
				for (int k = 0; k < num; ++k)
				{
					f[i + 1][j + weights[k]] = true;
				}
			}
		}
	}
}

bool BackTrace(int num, int size, int halfWeight, int curWeight, int curNum, int step)
{
	if (size == step)
	{
		if (curWeight == halfWeight)
		{
			return true;
		}
		return false;
	}
	
	for (int i = curNum; i < num; ++i)
	{
		if (curWeight + weights[i] <= halfWeight)
		{
			if (BackTrace(num, size, halfWeight, curWeight + weights[i], i + 1, step + 1))
			{
				return true;
			}
		}
	}
	return false;
}