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

/*
	排序，从小到大
*/
// 数组
int arr[1100];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	处理每一组数据，传入数据个数
*/
void Handle(int num);


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
	int count = 0;
	cin >> count;
	while (count--)
	{
		int num = 0;
		cin >> num;
		for (int i = 0; i < num; ++i)
		{
			cin >> arr[i];
		}
		// 分别处理每一组数据
		Handle(num);

		if (count)
		{
			cout << endl;
		}
	}
}

void Handle(int num)
{
	// 1.排序
	sort(arr, arr + num);
	// 左右指针，左闭右开
	int left = 0;
	int right = num;
	int total = 0;
	string ansStr;
	stringstream ss(ansStr);
	int num1 = 0;
	int num2 = 0;

	if (num > 0)
	{
		num1 = arr[left++];	
	}
	
	if (num > 1)
	{
		num2 = arr[left++];
	}
	int sumMin = num2 * 2 + num1;

	while (num > 3)
	{
		int maxNum1 = arr[--right];
		int maxNum2 = arr[--right];

		int sum1 = sumMin + maxNum1;
		int sum2 = maxNum1 + num1 + maxNum2 + num1;
		if (sum1 <= sum2)
		{
			ss << num1 << ' ' << num2 << '\n';		
			ss << num1 << '\n';				
			ss << maxNum2 << ' ' << maxNum1 << '\n';
			ss << num2 << '\n';
			
			total += sum1;
		}
		else
		{
			ss << num1 << ' ' << maxNum1 << '\n';		
			ss << num1 << '\n';
			ss << num1 << ' ' << maxNum2 << '\n';		
			ss << num1 << '\n';
			total += sum2;
		}
		num -= 2;
	}
	if (num == 3)
	{
		int maxNum1 = arr[--right];
		ss << num1 << ' ' << maxNum1 << '\n';		
		ss << num1 << '\n';				
		ss << num1 << ' ' << num2 << '\n';
		total += (maxNum1);
		total += (num2 + num1);	
	}
	else if (num == 2)
	{
		ss << num1 << ' ' << num2 << '\n';
		total += (num2);
	}
	else if (num == 1)
	{
		ss << num1 << '\n';
		total += num1;
	}
	// 没有0个数据!
	/*if (num == 0)
	{
		total = 0;
		ss << "";
	}*/
	cout << total << endl;
	cout << ss.str();
}
