#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//#define _MY_DEBUG_

// 最大罢工数
const int MAX_PARTY = 110;
// 最大天数
const int MAX_DAY = 4000;

/*
	
*/
void MainStructure();

/*
	处理过程
*/
void HandleProcess();

/*
	处理输入
*/
void Input(int &daysNum, int &partyNum, int hartales[]);

/*
	计算罢工天数
*/
int HartalesDay(int days[], int daysNum, int hartales[], int partyNum);


int main()
{
	//cout << "Test" << endl;	

	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "D:/2挑战编程/input/110203.inp";

	string outputStr = "D:/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

//	cout.rdbuf(fout.rdbuf());

#endif

	// 要处理的组数
	int count = 0;
	cin >> count;
	while (count--)
	{
		HandleProcess();
	}
}

void HandleProcess()
{
	// 1.处理输入
	// 总天数
	int daysNum = 0;
	// 政党数
	int partyNum = 0;
	// 政党的罢工指数
	int hartales[MAX_PARTY];
	// 天数
	int days[MAX_DAY];
	Input(daysNum, partyNum, hartales);

	// 计算罢工天数
	cout << HartalesDay(days, daysNum, hartales, partyNum) << endl;
}

int HartalesDay(int days[], int daysNum, int hartales[], int partyNum)
{
	memset(days, 0, sizeof(int) * MAX_DAY);
	//cout << sizeof(days) << endl;

	// 遍历每个政党
	for (int i = 0; i < partyNum; ++i)
	{
		// 罢工指数
		int num = hartales[i];
		// 遍历每一天，从1开始
		for (int j = 1; j <= daysNum; ++j)
		{
			// 1.是否是num的倍数？
			if (j % num == 0)
			{
				// 2.是周五、周六
				// 周五余数为6，周六余数为0
				if ((j % 7 == 6) || (j % 7 == 0))
				{
					continue;
				}
				// 不是周五、周六,将罢工数加一
				++days[j];
			}
		}
	}
	// 罢工总数
	int total = 0;
	for (int j = 1; j <= daysNum; ++j)
	{
		if (days[j] > 0)
		{
			++total;
		}
	}
	return total;
}

void Input(int &daysNum, int &partyNum, int hartales[])
{
	cin >> daysNum;
	cin >> partyNum;
	for (int i = 0; i < partyNum; ++i)
	{
		cin >> hartales[i];
	}
}