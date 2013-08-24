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

// 棋盘
int arr[16][16];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	传入n、k，返回解决方案数
*/
unsigned BackStace(int n, int k);

/*
	n：棋盘
	k：棋数
	step：当前进度
	ans：解数
	line：当前行数，下面的只能大于它	
*/
void Solve(int n, int k, int step, unsigned &ans, int line);

/*
	计算第line行的起始和结束位置
*/
void CalPosition(int n, int line, int &start, int &end);

void Test();

int main()
{
	MainStructure();
	//Test();
	return 0;
}

void Test()
{
	int start, end;
	CalPosition(4, 1, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 2, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 3, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 4, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 5, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 6, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 7, start, end);
	cout << start << " " << end << endl;
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
	int n, k;
	while (cin >> n >> k)
	{
		if (n == 0 && k == 0)
		{
			break;
		}
		unsigned ans = 0;
		ans = BackStace(n, k);
		cout << ans << endl;
	}
}



unsigned BackStace(int n, int k)
{
	unsigned ans = 0;
	memset(arr, 0, sizeof(arr));
	if (k > 2 * n)
	{
		return 0;
	}
	// 从第一行开始吧！
	Solve(n, k, 0, ans, 1);

	return ans;
}

void Solve(int n, int s, int step, unsigned &ans, int line)
{	
	if (step == s)
	{
		++ans;
		return;
	}
	else
	{
		// 下面的行挨个试
		for (int i = line; i < 2 * n; ++i)
		{ 
			// 对于当前的i行，计算其实位置和结束位置
			int start = 0;
			int end = 0;
			CalPosition(n, i, start, end);
			// 对于该行的每一格，挨个试
			for (int j = start; j <= end; j += 2)
			{
				bool isOK = true;
				// 看前面的行的当前格是否已经被填充
				for (int k = 1; k < line; ++k)
				{
					if (arr[k][j] == 1)
					{
						isOK = false;
						break;
					}
				}
				if (isOK)
				{
					// 如果可以，填充当前格子
					arr[i][j] = 1;
					// 向下回溯
					Solve(n, s, step + 1, ans, i + 1);
					// 不行：恢复
					arr[i][j] = 0;
				}
			}
		}
	}
}


void CalPosition(int n, int line, int &start, int &end)
{
	// 中间行的行数
	int middle = n;	
	if (line <= n)
	{
		int index = 1;
		start = 8;
		end = 8;
		while (index < line)
		{
			--start;
			++end;
			++index;
		}
	}
	else
	{
		int index = 2 * n - 1;
		start = 8;
		end = 8;
		while (index > line)
		{
			--start;
			++end;
			--index;
		}
	}
}