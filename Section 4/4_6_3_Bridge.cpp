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
	���򣬴�С����
*/
// ����
int arr[1100];


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	����ÿһ�����ݣ��������ݸ���
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
		// �ֱ���ÿһ������
		Handle(num);

		if (count)
		{
			cout << endl;
		}
	}
}

void Handle(int num)
{
	// 1.����
	sort(arr, arr + num);
	// ����ָ�룬����ҿ�
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
	// û��0������!
	/*if (num == 0)
	{
		total = 0;
		ss << "";
	}*/
	cout << total << endl;
	cout << ss.str();
}
