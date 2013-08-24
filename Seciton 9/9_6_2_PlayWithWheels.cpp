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

// �����
const int MAXV = 10001;

// ��λ
const int NUM_LENGTH = 4;

// һ��Ŀ�ʼ��־λ
const int START_FLAG = -1;

// һ��Ľ�����־λ
const int END_FLAG = -2;

bool discovered[MAXV];
// int parent[MAXV];



// ����ֹ����
int prevents[MAXV];
// ����ֹ�����ĸ���
int preventNum;

// ��ʼ��
int start;
// ��ֹ��
int to;

// ��ʱ����4Ϊ���� 
int nArr[NUM_LENGTH];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	��ȡ4λ����ƴ��һ������
*/	
void ReadNum(int &num);

int bfs();

/*
	��һ��4λ�����ĸ���λ�ŵ�һ��һά������ 
*/
void ParseIntToArr(int num);


/*
	��һ������Ϊ4��һά����ת��Ϊһ��4λ����
*/
int ParseArrToInt();

/*
	�ж�һ�����Ƿ���ֹ
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

	// һ��Ŀ�ʼ��־λ
	q.push(START_FLAG);
	q.push(start);
	discovered[start] = true;

	//// һ��Ľ�����־λ
	//q.push(END_FLAG);

	while (!q.empty())
	{
		int num = q.front();
		q.pop();
		// ����ǿ�ʼ��־λ
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
		//// ����ǽ�����־λ
		//if (num == END_FLAG)
		//{
		//	q.push(START_FLAG);
		//	continue;
		//}
		// ����ǽ��
		if (num == to)
		{
			return step;
		}
		// ����ʼ����ť
		ParseIntToArr(num);
		// 4��λ
		for (int i = 0; i < NUM_LENGTH; ++i)
		{
			// �ֱ��һ�ͼ�һ
			for (int j = -1; j <= 1; j += 2)
			{
				nArr[i] = (nArr[i] + j + 10) % 10;
				int newNum = ParseArrToInt();
				// ���û�б������
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