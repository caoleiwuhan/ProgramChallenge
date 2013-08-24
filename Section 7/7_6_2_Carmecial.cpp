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
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();


/*	
	判断是不是
*/
bool IsCarmail(unsigned num);

/*
	费马测试
*/
bool FemaTest(unsigned a, unsigned num);

/*
	计算pow
*/
unsigned PowMod(unsigned a, unsigned num, unsigned count);

/*
	Test
*/
void Test();

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

	/*ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());*/

#endif

	Process();
	//Test();
			
}

void Process()
{
	unsigned num = 0;
	while (cin >> num)
	{
		if (num == 0)
		{
			break;
		}
		if (IsCarmail(num))
		{
			cout << "The number " << num << " is a Carmichael number." << endl;
		}
		else
		{
			cout << num << " is normal." << endl;
		}		
	}
}

bool IsCarmail(unsigned num)
{
	// 1. 如果是质数，则：false
	// 2. 如果是合数，且满足费马检验，true	
	bool isHeshu = false;
	if (num % 2 == 0)
	{
		isHeshu = true;
	}
	if (!isHeshu)
	{
		double sNum = sqrt(double(num));
		for (int i = 3; i < sNum; i += 2)
		{
			if (num % i == 0)
			{
				isHeshu = true;
				break;
			}
		}
	}
	// 如果是质数，false
	if (!isHeshu)
	{
		return false;
	}
	// 费马测试
	for (unsigned i = 2; i < num; ++i)
	{
		if (!FemaTest(i, num))
		{
			return false;
		}
	}
	return true;
}

bool FemaTest(unsigned a, unsigned num)
{
	if (PowMod(a, num, num) == a)
	{
		return true;
	}
	return false;
}

unsigned PowMod(unsigned a, unsigned num, unsigned count)
{
	if (count == 1)
	{
		return (a % num);
	}
	// 如果是奇数
	if (count & 1)
	{
		unsigned tmp = PowMod(a, num, count / 2);
		tmp = tmp % num;
		tmp *= tmp;
		tmp = tmp % num;
		tmp = tmp * a;

		return (tmp % num);
	}
	else
	{
		int tmp = PowMod(a, num, count / 2);
		tmp = tmp % num;
		tmp *= tmp;
		return (tmp % num);
	}
}

void Test()
{
	FemaTest(1488, 1729);
}
