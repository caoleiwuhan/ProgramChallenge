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


// 数据结构，保存
unsigned f[14][14][14];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void dp();

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
			
}
void Process()
{
	//cout << "Test" << endl;
	int count = 0;
	cin >> count;
	int people, left, right;
	dp();

	while (count--)
	{
		cin >> people >> left >> right;
		cout << f[people][left][right] << endl;
	}
}


void dp()
{
	memset(f, 0, sizeof(f));

	f[1][1][1] = 1;
	for (int i = 2; i <= 13; ++i)
	{
		for (int j = 1; j <= 13; ++j)
		{
			for (int k = 1; k <= 13; ++k)
			{
				f[i][j][k] = f[i-1][j][k] * (i - 2) + f[i-1][j-1][k] + f[i-1][j][k-1];
			}
		}
	}
}

