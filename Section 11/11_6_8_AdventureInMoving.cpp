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
/*
	把这个问题复杂化了：
	f[i][j]:第i个加油站，油量为j
*/

// 邮箱容量为200
const int BOX = 201;

// 最多有100个加油站
const int STORE_NUM = 101;

// 加油站距离信息
int storeLength[STORE_NUM];
// 油价
int oilPrice[STORE_NUM];

// 距离为i时，邮箱有j升油，又加了k升油，花费的钱数
int dp[STORE_NUM][BOX][BOX];

int dp1[STORE_NUM][BOX][BOX];

int parent[STORE_NUM][BOX][BOX][3];

int parent1[STORE_NUM][BOX][BOX][3];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP(int length, int num);

void DP1(int length, int num);

int Solve(int length, int num);
int Solve1(int length, int num);

void Compare(int num);

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
		int length = 0;
		cin >> length;
		cin.ignore();

		string str;
		int len;
		int price;
		int num = 0;
		// 第0个
		storeLength[num] = 0;
		oilPrice[num++] = 0;


		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			stringstream ss(str);
			ss >> len >> price;
			if (len == 0)
			{
				oilPrice[num-1] = price;
			}
			else
			{
				if (len <= length)
				{
					storeLength[num] = len;
					oilPrice[num++] = price;
				}
			}
		}
		//DP(length, num);

		DP1(length, num);

		//Compare(num);

		//cout << Solve(length, num) << endl;
		cout << Solve1(length, num) << endl;

		if (count)
		{
			cout << endl;
		}
	}
}

void DP(int length, int num)
{
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < BOX; ++j)
		{
			for (int k = 0; k < BOX; ++k)
			{
				dp[i][j][k] = 0x7FFFFFFF;
				parent[i][j][k][0] = 0x7FFFFFFF;
				parent[i][j][k][1] = 0x7FFFFFFF;
				parent[i][j][k][2] = 0x7FFFFFFF;
			}
		}
	}
	// 起点位置，原有100升油，并且没有加油
	dp[0][100][0] = 0;
	
	// 一共i个加油站
	for (int i = 1; i < num && (storeLength[i-1] <= length); ++i)
	{
		for (int j = 0; j < BOX; ++j)
		{ // 邮箱剩余为j
			// 可以加的最大值
			int remain = 200 - j;
			for (int k = 0; k <= remain; ++k)
			{ // 准备在此加油k升
				
				int minCost = 0x7FFFFFFF;

				// 首先判断是否能在此加油:
				int distance = storeLength[i];
				// 检测前i-1个加油站的情况
				for (int s = i-1; s >= 0; --s)
				{
					int diff = distance - storeLength[s];
					// 距离前面的加油站为diff
					if (diff + j > 200)
					{ // 前面即使加满也无法满足要求
						continue;
					}
					for (int m = 0; m < BOX; ++m)
					{ // 在s处剩余m升，加了n升
						for (int n = 0; n < BOX; ++n)
						{ // 如果此处不成立，
							if (dp[s][m][n] == 0x7FFFFFFF)
							{
								continue;
							}
							//if (m + n > 200)
							//{
							//	continue;
							//}
							int lastOil = m + n;
							// 如果油量跑不到地方
							if (lastOil < diff)
							{
								continue;
							}
							if (lastOil - diff != j)
							{
								continue;
							}
							// 所有条件都满足，在此处加k升
							int curCost = dp[s][m][n] + k * oilPrice[i];
							if (curCost < minCost)
							{
								minCost = curCost;
								parent[i][j][k][0] = s;
								parent[i][j][k][1] = m;
								parent[i][j][k][2] = n;
							}
						}
					}
					dp[i][j][k] = minCost;
				}				
			}
		}
	}
}

int Solve(int length, int num)
{
	int ans = 0x7FFFFFFF;
	for (int i = num - 1; i >= 0; --i)
	{
		int distance = storeLength[i];
		int diff = length - distance;
		for (int j = 0; j < BOX; ++j)
		{
			for (int k = 0; k < BOX; ++k)
			{
				if (dp[i][j][k] != 0x7FFFFFFF)
				{
					if (j + k - diff >= 100)
					{
						if (dp[i][j][k] == 450550)
						{
							cout << "OK" << endl;
						}
						if (dp[i][j][k] < ans)
						{
							ans = dp[i][j][k];
							if (ans == 450550)
							{
								cout << "OK" << endl;
							}
						}
					}
				}
			}
		}
	}
	return ans;
}



void DP1(int length, int num)
{
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < BOX; ++j)
		{
			for (int k = 0; k < BOX; ++k)
			{
				dp1[i][j][k] = 0x7FFFFFFF;
				parent1[i][j][k][0] = 0x7FFFFFFF;
				parent1[i][j][k][1] = 0x7FFFFFFF;
				parent1[i][j][k][2] = 0x7FFFFFFF;
			}
		}
	}
	// 起点位置，原有100升油，并且没有加油
	dp1[0][100][0] = 0;
	
	// 一共i个加油站
	for (int i = 1; i < num && (storeLength[i-1] <= length); ++i)
	{
		// 首先判断是否能在此加油:
		int distance = storeLength[i];
		// 检测前i-1个加油站的情况
		for (int s = i-1; s >= 0; --s)
		{
			
			/*if (s == 0 && (oilPrice[0] == 0))
			{
				continue;
			}*/
			int diff = distance - storeLength[s];
			if (diff > 200)
			{
				continue;
			}

			// j可能的最大值
			int remainJ = 200 - diff;
			for (int j = 0; j <= remainJ; ++j)
			{				
				// 上一站一共的油量
				int lastOil = j + diff;

				// 可以加的最大值
				int remainK = 200 - j;

				for (int k = 0; k <= remainK; ++k)
				{ // 准备在此加油k升				
					int minCost = 0x7FFFFFFF;
					// 上一站加了m升
					for (int m = 0; m <= lastOil; ++m)
					{
						if (dp1[s][lastOil-m][m] != 0x7FFFFFFF)
						{
							int curCost = dp1[s][lastOil-m][m] + k * oilPrice[i];
							if (curCost < minCost)
							{
								minCost = curCost;
								parent1[i][j][k][0] = s;
								parent1[i][j][k][1] = lastOil - m;
								parent1[i][j][k][2] = m;
							}
						}
					}
					if (minCost < dp1[i][j][k])
					{
						dp1[i][j][k] = minCost;
					}
				}
			}
		}
	}
}

void Compare(int num)
{
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < BOX; ++j)
		{
			for (int k = 0; k < BOX; ++k)
			{
				if (dp[i][j][k] != dp1[i][j][k])
				{
					cout << "error" << endl;
				}
			}
		}
	}
}


int Solve1(int length, int num)
{
	int ans = 0x7FFFFFFF;
	for (int i = num - 1; i >= 0; --i)
	{
		int distance = storeLength[i];
		int diff = length - distance;
		for (int j = 0; j < BOX; ++j)
		{
			for (int k = 0; k < BOX; ++k)
			{
				if (dp1[i][j][k] != 0x7FFFFFFF)
				{
					if (j + k - diff >= 100)
					{						
						if (dp1[i][j][k] < ans)
						{
							ans = dp1[i][j][k];							
						}
					}
				}
			}
		}
	}
	return ans;
}
