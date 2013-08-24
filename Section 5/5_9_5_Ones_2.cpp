#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <stack>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	Test �߾��Ƚṹ
*/
void Test();

/*
	����
*/
int CountNum(int num);


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
		
}


void Process()
{
	int num = 0;
	while (cin >> num)
	{		
		int count = CountNum(num);
		cout << count << endl;
	}
}


int CountNum(int hp)
{
	int count = 1;
	int num = 1;
	while (true)
	{
		int tmp = num % hp;
		// ����ܱ�����
		if (tmp == 0)
		{
			return count;
		}
		// ��������num
		num *= 10;
		num += 1;
		num %= hp;

		++count;
	}
}