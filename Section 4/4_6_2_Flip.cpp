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

using namespace std;

//#define _MY_DEBUG_

// 存放饼
int cake[40];
// 排好序的
int ans[40];
// 临时数组
int tmp[40];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	从start到end，比较两个数组的数是否相同
	包括start、不包括end
*/
bool IsArrEqual(int start, int end);

/*
	从step开始，到end，找到cake中直径最大的数的index
*/
bool FindMaxFromArr(int start, int end, int &maxIndex);

/*
	翻转index处的数：1.先将index翻转到最顶部，然后再翻转到最底部
*/
void FlipNum(int start, int count);

/*
	增加step的值
*/
void IncreaseStep(int &step, int count);

/*
	翻转整数数组
*/
void SwapIntArr(int *arr, int start, int end);

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
	//fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());

#endif

	Process();
		
}

void Process()
{
	string str;
	while (getline(cin, str))
	{	
		stringstream ss(str);
		int count = 0;
		int num = 0;
		while (ss >> num)
		{
			cake[count++] = num;
		}
		// 显示第一行
		cout << str << endl;
		SwapIntArr(cake, 0, count);
		memcpy(ans, cake, sizeof(int) * count);
		// 从小到大排序
		sort(ans, ans + count);
		// 懒得写比较函数，直接翻转吧！使之变成从大到小排序
		SwapIntArr(ans, 0, count);

		int step = 0;
		// 如果没有排好序
		IncreaseStep(step, count);
		while (step < count)
		{				
			// 将index翻转的最顶部，然后翻转的step处
			FlipNum(step, count);

			//  step一次不一定只增加1！
			IncreaseStep(step, count);
		}
		cout << "0" << endl;
	}
}

bool FindMaxFromArr(int start, int end, int &maxIndex)
{
	if (start >= end)
	{
		maxIndex = -1;
		return false;
	}
	maxIndex = end - 1;
	int max = cake[end - 1];

	for (int i = end - 2; i >= start; --i)
	{
		if (cake[i] > max)
		{
			max = cake[i];
			maxIndex = i;
		}
	}
	// 如果是第一个
	if (maxIndex == end - 1)
	{
		for (int i = end - 2; i >= start; --i)
		{
			if (cake[i] == max)
			{				
				--maxIndex;
			}
			else
			{
				break;
			}
		}
		return true;
	}	
	return false;
}

void FlipNum(int start, int count)
{
	if (start >= count)
	{
		return;
	}
	int index;
	// 从step开始，到end，找到cake中直径最大的数的index
	bool isOK = FindMaxFromArr(start, count, index);

	// 1.将index翻转到最顶部
	if (!isOK)
	{
		SwapIntArr(cake, index, count);
		cout <<(index + 1) << " ";
	}
	// 2.此时最大值已经在顶部，翻转从start到count的数即可
	SwapIntArr(cake, start, count);
	cout <<	(start + 1) << " ";
}

void IncreaseStep(int &step, int count)
{
	for (int i = step; i < count; ++i)
	{
		if (cake[i] == ans[i])
		{
			++step;
		}
		else
		{
			break;
		}
	}
}

void SwapIntArr(int *arr, int start, int end)
{
	int middle = start + (end - start) / 2;
	for (int i = start, j = 1; i < middle; ++i, ++j)
	{
		swap(arr[i], arr[end - j]);
	}
}