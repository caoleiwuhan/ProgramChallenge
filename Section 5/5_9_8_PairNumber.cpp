#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

#define _MY_DEBUG_


// sum
int sum[50];
// arr
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
	����
*/
bool IsSum(int sumNum, int num);

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
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
	ifstream fin;
	fin.open(inputStr);	
	

	cin.rdbuf(fin.rdbuf());	

	/*ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());*/

#endif

	Process();
			
}

void Process()
{
	int num = 0;
	while (cin >> num)
	{
		int sumNum = num * (num - 1) / 2;
		for (int i = 0; i < sumNum; ++i)
		{
			cin >> sum[i];
		}
		if (IsSum(sumNum, num))
		{
			for (int i = 0; i < num; ++i)
			{
				cout << arr[i] << ' ';
			}
			cout << endl;
		}
		else
		{
			cout << "Impossible" << endl;
		}
	}
}

bool IsSum(int sumNum, int num)
{
	return false;
}