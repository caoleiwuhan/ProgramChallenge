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

//#define _MY_DEBUG_

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	����smith��
*/
unsigned SmithNumber(unsigned num);

/*
	����num����λ֮��
*/
unsigned SumOfNum(unsigned num);

/*
	����num����������λ֮��
*/
unsigned SumOfFactorNum(unsigned num);

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
		unsigned num = 0;
		cin >> num;
		unsigned ans = SmithNumber(num);
		cout << ans << endl;
	}	
}

unsigned SmithNumber(unsigned num)
{
	// 1.
	for (unsigned tmp = num + 1; ; ++tmp)
	{	
		// �������λ֮��
		unsigned num1 = SumOfNum(tmp);
		// ��������������λ֮�ͣ����Ϊ��������Ϊ0
		unsigned num2 = SumOfFactorNum(tmp);
		if (num1 == num2)
		{
			return tmp;
		}
	}
}

unsigned SumOfNum(unsigned num)
{
	unsigned ans = 0;
	while (num)
	{
		ans += (num % 10);
		num /= 10;
	}
	return ans;
}

unsigned SumOfFactorNum(unsigned num)
{
	if (num < 4)
	{
		return 0;
	}
	bool isPrime = true;
	unsigned ans = 0;
	while (num % 2 == 0)
	{
		num /= 2;
		ans += 2;
		isPrime = false;
	}
	double sNum = sqrt(double(num)) + 1;
	for (unsigned i = 3; i <= sNum; i += 2)
	{
		while (num % i == 0)
		{
			ans += SumOfNum(i);
			num /= i;
			sNum = sqrt(double(num)) + 1;
			isPrime = false;
		}
	}
	if (num != 1)
	{
		ans += SumOfNum(num);
	}
	if (isPrime)
	{
		ans = 0;
	}
	return ans;
}
