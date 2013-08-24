#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

#define _MY_DEBUG_


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	Handle()
*/
unsigned Handle(int people, int left, int right);

/*
	Queue
*/
void QueueBackTrace(int *num, int peopoe, int step, int left, int right, 
	int curLeft, int curRight, int &curMax, unsigned &ans);

/*
	最长上升子序列数
*/
int LongestIncreaseSequence(int *num, int size);


/*
	最长下降子序列数
*/
int LongestDecreaseSequence(int *num, int size);

void LeftRightNum(int *num, int size, int &leftNum, int &rightNum);

/*
	全排列数生成
*/
void Pemutation(int *num, int size, int step, int &ans);

/*
	打印intarr
*/
void PrintIntArr(int *num, int size);

/*
	测试全排列生成
*/
void TestPumutation();

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
	//TestPumutation();
			
}
void Process()
{
	//cout << "Test" << endl;
	int count = 0;
	cin >> count;
	int people, left, right;
	while (count--)
	{
		cin >> people >> left >> right;
		cout << Handle(people, left, right) << endl;
	}
}

unsigned Handle(int people, int left, int right)
{
	unsigned ans = 0;
	int *num = new int[people];
	for (int i = 0; i < people; ++i)
	{
		num[i] = i + 1;
	}
	int curMax = 1;
	int curLeft = 0;
	int curRight = 0;
	
	QueueBackTrace(num, people, 0, left, right, 0, 0, curMax, ans);

	delete [] num;

	return ans;
}

void QueueBackTrace(int *num, int people, int step, int left, int right, 
	int curLeft, int curRight, int &curMax, unsigned &ans)
{
	if (step == people)
	{
		LeftRightNum(num, people, curLeft, curRight);
		
		if (curLeft == left && curRight == right)
		{
			++ans;
		}
		return;
	}
	for (int i = step; i < people; ++i)
	{
		swap(*(num + step), *(num + i));
		curLeft = LongestIncreaseSequence(num, i + 1);		
		if (curLeft <= left)
		{
			QueueBackTrace(num, people, step + 1, left, right, curLeft, curRight, curMax, ans);
		}

		swap(*(num + i), *(num + step));
	}
}

void Pemutation(int *num, int size, int step, int &ans)
{
	if (step == size)
	{
		PrintIntArr(num, size);
		++ans;
		return;
	}
	for (int i = step; i < size; ++i)
	{
		swap(*(num + step), *(num + i));
		Pemutation(num, size, step + 1, ans);
		swap(*(num + i), *(num + step));
	}
}

void PrintIntArr(int *num, int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << num[i] << ' ';
	}
	cout << endl;
}

void TestPumutation()
{
	int size = 13;
	int *num = new int[size];
	for (int i = 0; i < size; ++i)
	{
		num[i] = i + 1;
	}
	
	int ans = 0;
	Pemutation(num, size, 0, ans);

	delete []num;
	cout << ans << endl;
}

int LongestIncreaseSequence(int *num, int size)
{
	if (size == 0)
	{
		return 0;
	}

	int curMax = num[0];
	int ans = 1;
	for (int i = 1; i < size; ++i)
	{
		if (num[i] > curMax)
		{
			curMax = num[i];
			++ans;
		}
	}
	return ans;
}

int LongestDecreaseSequence(int *num, int size)
{
	if (size == 0)
	{
		return 0;
	}
	if (size == 1)
	{
		return 1;
	}

	int curMax = num[size - 1];
	int ans = 1;
	for (int i = size - 2; i >= 0; --i)
	{
		if (num[i] > curMax)
		{
			curMax = num[i];
			++ans;
		}
	}
	return ans;
}

void LeftRightNum(int *num, int size, int &leftNum, int &rightNum)
{
	leftNum = LongestIncreaseSequence(num, size);
	rightNum = LongestDecreaseSequence(num, size);
}