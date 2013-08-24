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
#include <queue>


using namespace std;

//#define _MY_DEBUG_

// 最大数
const int MAXV = 10001;

// 数位
const int NUM_LENGTH = 4;

// 一层的开始标志位
const int START_FLAG = -1;

// 一层的结束标志位
const int END_FLAG = -2;

bool discovered[MAXV];
// int parent[MAXV];



// 被禁止的数
int prevents[MAXV];
// 被禁止的数的个数
int preventNum;

// 起始数
int start;
// 终止数
int to;

// 临时保存4为整数 
int nArr[NUM_LENGTH];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	读取4位数，拼成一个整数
*/	
void ReadNum(int &num);

int bfs();

/*
	将一个4位整数的各个位放到一个一维数组中 
*/
void ParseIntToArr(int num);


/*
	将一个长度为4的一维数组转化为一个4位整数
*/
int ParseArrToInt();

/*
	判断一个数是否被阻止
*/
bool IsNumPrevent(int num);

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
		ReadNum(start);
		ReadNum(to);

		cin >> preventNum;
		for (int i = 0; i < preventNum; ++i)
		{
			ReadNum(prevents[i]);
		}
		if (start == to)
		{
			cout << 0 << endl;
		}
		else
		{
			cout << bfs() << endl;
		}
	}
}

int bfs()
{
	int step = -1;
	memset(discovered, 0, sizeof(discovered));
	queue<int> q;

	//if (IsNumPrevent(start))
	//{
	//	return -1;
	//}

	// 一层的开始标志位
	q.push(START_FLAG);
	q.push(start);
	discovered[start] = true;

	//// 一层的结束标志位
	//q.push(END_FLAG);

	while (!q.empty())
	{
		int num = q.front();
		q.pop();
		// 如果是开始标志位
		if (num == START_FLAG)
		{
			if (q.size() == 0)
			{
				break;
			}
			++step;
			q.push(START_FLAG);
			continue;
		}
		//// 如果是结束标志位
		//if (num == END_FLAG)
		//{
		//	q.push(START_FLAG);
		//	continue;
		//}
		// 如果是结果
		if (num == to)
		{
			return step;
		}
		// 否则开始摁按钮
		ParseIntToArr(num);
		// 4个位
		for (int i = 0; i < NUM_LENGTH; ++i)
		{
			// 分别加一和减一
			for (int j = -1; j <= 1; j += 2)
			{
				nArr[i] = (nArr[i] + j + 10) % 10;
				int newNum = ParseArrToInt();
				// 如果没有被处理过
				if (!discovered[newNum])
				{					
					if (!IsNumPrevent(newNum))
					{
						discovered[newNum] = true;
						q.push(newNum);
					}
				}
				nArr[i] = (nArr[i] - j + 10) % 10;
			}
		}
	}

	return -1;
}

void ReadNum(int &num)
{
	int sum = 0;
	int tmp = 0;
	for (int i = 0; i < NUM_LENGTH; ++i)
	{
		cin >> tmp;
		sum = sum * 10 + tmp;
	}
	num = sum;
}

void ParseIntToArr(int num)
{
	memset(nArr, 0, sizeof(nArr));
	int index = 0;	
	while (num)
	{		
		nArr[index++] = num % 10;
		num /= 10;
	}
}

int ParseArrToInt()
{
	int num = 0;
	for (int i = NUM_LENGTH - 1; i >= 0; --i)
	{
		num = num * 10 + nArr[i];
	}
	return num;
}

bool IsNumPrevent(int num)
{
	for (int k = 0; k < preventNum; ++k)
	{
		if (num == prevents[k])
		{
			return true;
		}
	}
	return false;
}