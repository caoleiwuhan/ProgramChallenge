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

// ��ű�
int cake[40];
// �ź����
int ans[40];
// ��ʱ����
int tmp[40];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	��start��end���Ƚ�������������Ƿ���ͬ
	����start��������end
*/
bool IsArrEqual(int start, int end);

/*
	��step��ʼ����end���ҵ�cake��ֱ����������index
*/
bool FindMaxFromArr(int start, int end, int &maxIndex);

/*
	��תindex��������1.�Ƚ�index��ת�������Ȼ���ٷ�ת����ײ�
*/
void FlipNum(int start, int count);

/*
	����step��ֵ
*/
void IncreaseStep(int &step, int count);

/*
	��ת��������
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
		// ��ʾ��һ��
		cout << str << endl;
		SwapIntArr(cake, 0, count);
		memcpy(ans, cake, sizeof(int) * count);
		// ��С��������
		sort(ans, ans + count);
		// ����д�ȽϺ�����ֱ�ӷ�ת�ɣ�ʹ֮��ɴӴ�С����
		SwapIntArr(ans, 0, count);

		int step = 0;
		// ���û���ź���
		IncreaseStep(step, count);
		while (step < count)
		{				
			// ��index��ת�������Ȼ��ת��step��
			FlipNum(step, count);

			//  stepһ�β�һ��ֻ����1��
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
	// ����ǵ�һ��
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
	// ��step��ʼ����end���ҵ�cake��ֱ����������index
	bool isOK = FindMaxFromArr(start, count, index);

	// 1.��index��ת�����
	if (!isOK)
	{
		SwapIntArr(cake, index, count);
		cout <<(index + 1) << " ";
	}
	// 2.��ʱ���ֵ�Ѿ��ڶ�������ת��start��count��������
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