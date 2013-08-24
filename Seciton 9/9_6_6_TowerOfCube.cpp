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

//#define _MY_DEBUG_

const int MAXV = 700;
// 六个面
const int FACE = 6;

int Cube[MAXV][FACE];

// DP的
int f[MAXV][FACE];

// 父节点的编号
int parentNum[MAXV][FACE];
// 当前节点顶面的颜色
int parentColorIndex[MAXV][FACE];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP(int cubeNum, int &ansNum, int &ansIndex, int &ansMax);

/*
	根据color找序号，没有返回-1
*/
int FindColorIndex(int cubeNum, int color);

/*
	根据index，返回与他相对的颜色
*/
int FindInverseColorOfIndex(int cubeNum, int index);

/*
	输出结果
*/
void PrintResult(int ansNum, int ansIndex, int ansMax);

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
	int count = 1;
	int cubeNum = 0;
	while (cin >> cubeNum)
	{
		if (cubeNum == 0)
		{
			break;
		}
		// 初始化
		memset(Cube, 0, sizeof(Cube));
		memset(parentNum, 0, sizeof(parentNum));
		memset(parentColorIndex, 0, sizeof(parentColorIndex));

		int color = 0;
		for (int i = 1; i <= cubeNum; ++i)
		{			
			for (int j = 0; j < FACE; ++j)
			{
				cin >> color;
				Cube[i][j] = color;
			}
		}
		int ansNum = 0;
		int ansIndex = 0;
		int ansMax = 0;
		DP(cubeNum, ansNum, ansIndex, ansMax);
		if (count != 1)
		{
			cout << endl;
		}

		cout << "Case #" << count << endl;
		cout << ansMax << endl;
		PrintResult(ansNum, ansIndex, ansMax);
		
		++count;
	}
}

void DP(int cubeNum, int &ansNum, int &ansIndex, int &ansMax)
{
	ansNum = 1;
	ansIndex = 0;
	ansMax = 1;

	// 初始化
	for(int j = 1; j <= cubeNum; ++j)
	{
		for (int i = 0; i < FACE; ++i)
		{
			f[j][i] = 1;
			//parentNum[1][i] = -1;
			//// 这里i表示的是在其父节点朝上的序号
			//parentColorIndex[1][i] = -1;
		}
	}

	for (int i = 2; i <= cubeNum; ++i)
	{
		// 从i-1到1遍历，寻找可以与其相接的正方体
		for (int j = i - 1; j >= 1; --j)
		{
			// 表示i的六个面
			for (int k = 0; k < FACE; ++k)
			{
				// 表示j的六个面
				for (int s = 0; s < FACE; ++s)
				{
					int color1 = Cube[i][k];
					int color2 = FindInverseColorOfIndex(j, s);
					if (color1 == color2)
					{
						int curNum = f[j][s] + 1;
						if (curNum > f[i][k])
						{
							f[i][k] = curNum;
							parentNum[i][k] = j;
							parentColorIndex[i][k] = s;
							if (curNum > ansMax)
							{								
								ansMax = curNum;
								ansNum = i;
								ansIndex = k;
							}
						}
					}
				}
			}
		}
	}
}

int FindColorIndex(int cubeNum, int color)
{
	for (int i = 0; i < FACE; ++i)
	{
		if (Cube[cubeNum][i] == color)
		{
			return i;
		}
	}
	return -1;
}

int FindInverseColorOfIndex(int cubeNum, int index)
{
	// 保证index为从0到FACE
	// 如果是偶数
	if (index % 2 == 0)
	{
		return Cube[cubeNum][index + 1];
	}
	else
	{
		return Cube[cubeNum][index - 1];
	}	
}

void PrintResult(int ansNum, int ansIndex, int ansMax)
{
	
	if (parentNum[ansNum][ansIndex] != 0)
	{
		PrintResult(parentNum[ansNum][ansIndex], parentColorIndex[ansNum][ansIndex], ansMax);
	}
	
	cout << ansNum << ' ';
	switch(ansIndex)
	{
	case 0:
		cout << "front" << endl;
		break;
	case 1:
		cout << "back" << endl;
		break;

	case 2:
		cout << "left" << endl;
		break;

	case 3:
		cout << "right" << endl;
		break;

	case 4:
		cout << "top" << endl;
		break;

	case 5:
		cout << "bottom" << endl;
		break;
	}
	
}