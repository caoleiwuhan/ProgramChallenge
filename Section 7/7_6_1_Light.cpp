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
	�ж����һյ���ǿ����ǹأ�
		����true
		�أ�false
*/
bool IsOpen(unsigned num);



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
	unsigned num = 0;
	while (cin >> num)
	{
		if (num == 0)
		{
			break;
		}
		if (IsOpen(num))
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}
}

bool IsOpen(unsigned num)
{
	unsigned sNum = (int)sqrt(double (num));
	if (sNum *sNum == num)
	{
		return true;
	}
	return false;
}