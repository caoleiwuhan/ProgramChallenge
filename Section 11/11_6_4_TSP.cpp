#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>
#include <hash_map>


using namespace std;

#define _MY_DEBUG_

const int ROW = 11;
const int COL = 101;

int matrix[ROW][COL];

int s[ROW][COL];
int parent[ROW][COL];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	返回权值最小的行：s[res][col]
*/
int DP(int row, int col);

/*
	打印结果
*/
void PrintAnswer(int curRow, int curCol, int row, int col);

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
	string str;
	int row;
	int col;
	int index = 0;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		stringstream ss(str);
		ss >> row >> col;
				
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				cin >> matrix[i][j];
			}
		}
		int ans = DP(row, col);
		PrintAnswer(ans, 1, row, col);
		cout << endl;
		cout << s[ans][1] << endl;
		cin.get();
	}	
}

int DP(int row, int col)
{
	memset(s, 0, sizeof(s));
	memset(parent, 0, sizeof(parent));

	for (int i = 1; i <= row; ++i)
	{
		s[i][col] = matrix[i-1][col-1];
		// 第一列特殊标记
		parent[i][col] = -1;
	}
	for (int j = col-1; j > 0; --j)
	{
		for (int i = 1; i <= row; ++i)
		{
			int tmp = s[i][j+1];
			parent[i][j] = 1;
			if (i != 1)
			{
				if (s[i-1][j+1] <= tmp)
				{
					tmp = s[i-1][j+1];
					parent[i][j] = 0;
				}
			}
			else
			{
				// 如果是第一行，从第row行找
				if (s[row][j+1] < tmp)
				{
					tmp = s[row][j+1];
					parent[i][j] = 0;
				}
			}

			if (i != row)
			{
				if (s[i+1][j+1] < tmp)
				{
					tmp = s[i+1][j+1];
					parent[i][j] = 2;
				}
			}
			else
			{	// 如果是第row行，从第一行找
				if (s[1][j+1] < tmp)
				{
					tmp = s[1][j+1];
					parent[i][j] = 2;
				}
			}
			s[i][j] = tmp + matrix[i-1][j-1];
		}
	}
	int ans = 0x7FFFFFFF;
	int res = 1;
	for (int i = 1; i <= row; ++i)
	{
		if (s[i][1] < ans)
		{
			ans = s[i][1];
			res = i;
		}
	}
	return res;
}

//void PrintAnswer(int curRow, int curCol, int row, int col, int ans)
//{
//	if (curCol != 1)
//	{
//		int tmp = curRow;
//		curRow += (parent[curRow][curCol] - 1);
//		curRow = curRow % row;
//		if (curRow == 0)
//		{
//			curRow = 1;
//		}
//		PrintAnswer(curRow, curCol - 1, row, col, ans);
//		curRow = tmp;
//	}
//	
//	cout << curRow;
//	if (curCol != col)
//	{
//		cout << ' ';
//	}
//}

void PrintAnswer(int curRow, int curCol, int row, int col)
{
	while (curCol != col)
	{
		cout << curRow << ' ';
		curRow += (parent[curRow][curCol] - 1);
		curRow = curRow % row;
		if (curRow == 0)
		{
			curRow = row;
		}
		++curCol;
	}
	
	cout << curRow;	
}