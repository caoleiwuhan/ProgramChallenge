#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

//#define _MY_DEBUG_

// ����arr�Ĵ���
int arr[20];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	����ϵ��
*/
unsigned int CalNum(int arr[], int k, int n);

/*
	���������
*/
unsigned int ZuHeShu(int n, int i);

void Test();

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
	//fout.open(outputStr.c_str());

	//cout.rdbuf(fout.rdbuf());
#endif

	Process();
	//Test();
		
}

void Process()
{
	unsigned n, k;
	while (cin >> n >> k)
	{
		for (int i = 0; i < k; ++i)
		{
			cin >> arr[i];
		}
		unsigned int total = CalNum(arr, k, n);
		cout << total << endl;
	}
}

unsigned int CalNum(int arr[], int k, int n)
{	
	unsigned int ans = 1;
	for (int i = 0; i < k; ++i)
	{
		ans *= ZuHeShu(n, arr[i]);
		n -= arr[i];
	}
	return ans;
}

unsigned int ZuHeShu(int n, int i)
{
	if (n == 0 || i == 0)
	{
		return 1;
	}
	if (n / i > 2)
	{
		i = n - i;
	}
	unsigned int ans = 1;
	for (int index = n; index > (n - i); --index)
	{
		ans *= (unsigned int)index;
	}
	for (int index = 2; index <= i; ++index)
	{
		ans /= (unsigned int)index;
	}
	return ans;
}

void Test()
{
	cout << ZuHeShu(4, 0) << endl;
	cout << ZuHeShu(4, 1) << endl;
	cout << ZuHeShu(4, 2) << endl;
	cout << ZuHeShu(4, 3) << endl;
	cout << ZuHeShu(4, 4) << endl;

}