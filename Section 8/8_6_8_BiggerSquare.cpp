#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

// 最大边长
const int MAX_LENGTH = 51;

// 结果正方形结构
struct Square
{
	int posx;
	int posy;
	int length;
	
	Square(int _posx, int _posy, int _length) 
		: posx(_posx), posy(_posy), length(_length) {}
};

// 保存结果
vector<Square> bestSquareAns;
vector<Square> curSquareAns;

// 所需小正方形的个数
int squareNum = MAX_LENGTH * MAX_LENGTH;

//
bool map[MAX_LENGTH][MAX_LENGTH];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	回溯
	len:边长
	cur:当前正方形的边长，后面的只能比它小
	curSquareNum:当前正方形个数
*/
void BackTrace(int len, int cur, int curSquareNum, int curMaxLen);

/*
	判断是否已经全部覆盖
*/
bool IsOK(int len);

void FindMaxUncoveredSquare(int len, int maxUnCoverLen, int &sLength, int &posx, int &posy);

/*
	将正方形涂黑，或涂白
*/
void CoveredSquare(int sLength, int posx, int posy, bool black);

void CopyVecSquare(vector<Square> &to, vector<Square> &from);

void PrintSquare(vector<Square> &ans, int len);

/*
	检查一行是否为black
*/
bool IsRowOK(int row, int start, int end, bool black, int len);


/*
	检查一列是否为black
	首先判断是否出了边界
*/
bool IsColOK(int col, int start, int end, bool black, int len);

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
	int count = 0;
	cin >> count;
	while (count--)
	{
		int len = 0;
		cin >> len;
		memset(map, 0, sizeof(map));

		BackTrace(len, len, 0, len - 1);
		PrintSquare(bestSquareAns, squareNum);
	}
}

void BackTrace(int len, int cur, int curSquareNum, int curMaxLen)
{
	// 判断是否已经全部覆盖
	if (IsOK(len))
	{
		if (curSquareNum < squareNum)
		{
			squareNum = curSquareNum;
			CopyVecSquare(bestSquareAns, curSquareAns);
		}
		return;
	}
	
	// 寻找没有覆盖的最大正方形

	int maxUnCoverLen;
	for (maxUnCoverLen = curMaxLen; maxUnCoverLen > 0; --maxUnCoverLen)
	{
		int sLength = 0;
		int posx, posy;
		FindMaxUncoveredSquare(len, maxUnCoverLen, sLength, posx, posy);
		if (sLength != maxUnCoverLen)
		{
			continue;
		}
		curSquareAns.push_back(Square(posx, posy, sLength));
		CoveredSquare(sLength, posx, posy, true);

		// 向下回溯
		BackTrace(len, cur, curSquareNum + 1, sLength);
		curSquareAns.pop_back();
		CoveredSquare(sLength, posx, posy, false);	
	}			
}

bool IsOK(int len)
{
	for (int i = 1; i <= len; ++i)
	{
		for (int j = 1; j <= len; ++j)
		{
			if (!map[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void FindMaxUncoveredSquare(int len, int maxUnCoverLen, int &sLength, int &posx, int &posy)
{
	//sLength = 1;
	for (int i = 1; i <= len; ++i)
	{
		for (int j = 1; j <= len; ++j)
		{			
			if (!map[i][j])
			{
				int curx = i;
				int cury = j;
				int curlength = 1;

				for (int length = 2; length <= maxUnCoverLen; ++length)
				{
					if (IsRowOK(i + length - 1, j, j + length - 1, false, len)
						&& IsColOK(j + length - 1, i, i + length - 1, false, len))
					{
						curlength = length;
					}
					else
					{
						break;
					}
				}
				if (curlength > sLength)
				{
					sLength = curlength;
					posx = curx;
					posy = cury;
				}
			}
		}
	}
}

void CoveredSquare(int sLength, int posx, int posy, bool black)
{
	for (int i = posx; i < posx + sLength; ++i)
	{
		for (int j = posy; j < posy + sLength; ++j)
		{
			map[i][j] = black;
		}
	}
}

void CopyVecSquare(vector<Square> &to, vector<Square> &from)
{
	to.clear();
	int slen = from.size();
	for (int i = 0; i < slen; ++i)
	{
		Square s(from[i].posx, from[i].posy, from[i].length);
		to.push_back(s);
	}		
}

void PrintSquare(vector<Square> &ans, int sNum)
{
	cout << sNum << endl;
	for (int i = 0; i < sNum; ++i)
	{
		cout << ans[i].posx << ' ' << ans[i].posy << ' ' << ans[i].length << endl;
	}
}

bool IsRowOK(int row, int start, int end, bool black, int len)
{
	if (start < 1 || end > len)
	{
		return false;
	}

	for (int i = start; i <= end; ++i)
	{
		if (map[row][i] != black)
		{
			return false;
		}
	}
	return true;
}

bool IsColOK(int col, int start, int end, bool black, int len)
{
	if (start < 1 || end > len)
	{
		return false;
	}

	for (int i = start; i <= end; ++i)
	{
		if (map[i][col] != black)
		{
			return false;
		}
	}
	return true;
}