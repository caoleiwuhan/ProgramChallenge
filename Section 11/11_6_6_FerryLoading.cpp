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

// 汽车长度
int carLength[10001];

int s[10001][10001];
int parent[10001][10001];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP(int boatLength, int carNum);

int Solve(int boatLength, int &left, int &right);

void PrintAnswer(int count, int left, int right);

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
	//TestBinarySearch();
			
}
void Process()
{
	int count = 0;
	cin >> count;
	while (count--)
	{
		int boatLength = 0;
		cin >> boatLength;
		boatLength *= 100;
		int carNum = 0;
		int carLen = 0;
		while (cin >> carLen)
		{
			if (carLen == 0)
			{
				break;
			}
			carLength[carNum++] = carLen;
		}
		DP(boatLength, carNum);
		int ans = 0;
		int left = 0;
		int right = 0;
		ans = Solve(boatLength, left, right);

		cout << ans << endl;
		PrintAnswer(ans, left, right);

		if (count)
		{
			cout << endl;
		}
	}
}

void DP(int boatLength, int carNum)
{	
	memset(s, 0, sizeof(s));
	memset(parent, 0, sizeof(parent));

	s[carLength[0]][0] = 1;
	parent[carLength[0]][0] = 1;

	s[0][carLength[0]] = 1;
	parent[0][carLength[0]] = 2;
	
	// 第t辆车,从第2辆车开始
	for (int t = 1; t < carNum; ++t)
	{
		for (int i = 0; i <= boatLength; ++i)
		{
			for (int j = 0; j <= boatLength; ++j)
			{
				if (s[i][j] == t)
				{
					// 如果可以放到左边
					if (i + carLength[t] <= boatLength)
					{
						s[i + carLength[t]][j] = s[i][j] + 1;
						parent[i + carLength[t]][j] = 1;
					}
					// 如果可以放到右边
					if (j + carLength[t] <= boatLength)
					{
						s[i][j + carLength[t]] = s[i][j] + 1;
						parent[i][j + carLength[t]] = 2;
					}
				}
			}
		}
	}
	
}

int Solve(int boatLength, int &left, int &right)
{
	int ans = 0;
	left = 0;
	right = 0;

	for (int i = 0; i <= boatLength; ++i)
	{
		for (int j = 0; j <= boatLength; ++j)
		{
			if (s[i][j] > ans)
			{
				ans = s[i][j];
				left = i;
				right = j;
			}
		}
	}
	return ans;
}

void PrintAnswer(int count, int left, int right)
{
	if (count != 1)
	{
		if (parent[left][right] == 1)
		{
			PrintAnswer(count - 1, left - carLength[count - 1], right);
		}
		if (parent[left][right] == 2)
		{
			PrintAnswer(count - 1, left, right - carLength[count - 1]);
		}
	}
	
	if (parent[left][right] == 1)
	{
		cout << "port" << endl;
	}
	if (parent[left][right] == 2)
	{
		cout << "starboard" << endl;
	}
}