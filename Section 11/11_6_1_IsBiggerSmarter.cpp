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

struct Elephent
{
	int ID;
	int weight;
	int IQ;

	Elephent()
	{}

	Elephent(int _ID, int _weight, int _IQ)
		: ID(_ID), weight(_weight), IQ(_IQ)
	{}

};

Elephent elephents[1001];

int decrease[101];

// 保存结果
int ans[1001][1001];

// DP
int dp[1001][1001];

int sequnce[1001];

/*
	按照大小的体重从小到大排序
*/
bool WeightCmp(const Elephent &e1, const Elephent &e2)
{
	if (e1.weight != e2.weight)
	{
		return (e1.weight < e2.weight);
	}
	return (e1.IQ > e2.IQ);
}


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();


/*
	计算最长递减子序列
*/
int Solve(int eNum);


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
	int index = 0;
	int w;
	int iq;

	// 初始化
	for (int i = 1, j = 100; i <= 100; ++i, --j)
	{
		decrease[i] = j;
	}

	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		stringstream ss(str);
		ss >> w >> iq;
		Elephent e(index, w, iq);
		elephents[index++] = e;
	}
	sort(elephents, elephents + index, WeightCmp);
	// 最长递减子序列
	int ans = Solve(index);
	cout << ans << endl;
	for (int i = 1; i <= ans; ++i)
	{
		cout << sequnce[i] << endl;
	}
}

//int Solve(int eNum)
//{
//	int res = 0;
//	memset(dp, 0, sizeof(dp));
//	memset(ans, 0, sizeof(ans));
//	
//	for (int i = 0; i < 101; ++i)
//	{
//		dp[0][i] = 0;
//	}
//
//	for (int i = 1; i < eNum; ++i)
//	{
//		for (int j = 1; j < 101; ++j)
//		{
//			int tmp = dp[i-1][j-1];
//			if (elephents[i-1].IQ == decrease[j] * 100)
//			{
//				++tmp;
//				ans[i][j] = 1;
//			}
//			if (dp[i][j-1] > tmp)
//			{
//				tmp = dp[i][j-1];
//				ans[i][j] = 2;
//			}
//			if (dp[i-1][j] > tmp)
//			{
//				tmp = dp[i-1][j];
//				ans[i][j] = 2;
//			}
//			dp[i][j] = tmp;
//		}
//	}
//}

int Solve(int eNum)
{
	int res = 0;
	memset(dp, 0, sizeof(dp));
	memset(ans, 0, sizeof(ans));
	
	for (int i = 0; i < 1001; ++i)
	{
		dp[0][i] = 0;
	}
	for (int i = 0; i < 1001; ++i)
	{
		dp[i][0] = 0;
	}

	for (int i = 1; i < eNum; ++i)
	{
		for (int j = 1; j <= i ; ++j)
		{ // 前i个字母中有j个下降序，其最前面一个的index为dp[i][j]
			if (dp[i-1][j])
			{
				dp[i][j] = dp[i-1][j];
				ans[i][j] = 2;
			}			
			/*
				dp[i][j] = dp[i-1][j-1]
				dp[i-1][j]
			*/
			else if (dp[i-1][j-1])
			{
				int curIndex = dp[i-1][j-1];
				if (elephents[curIndex-1].weight > elephents[i-1].weight &&
					elephents[curIndex-1].IQ < elephents[i-1].IQ)
				{
					dp[i][j] = i;
					ans[i][j] = 1;
				}
			}
		}
	}
	for (int i = eNum; i >= 0; --i)
	{
		if (dp[eNum][i])
		{
			res = i;
		}
	}
	// 构造结果集
	int i = eNum;
	int j = res;
	int index = res;

	while (ans[i][j])
	{
		sequnce[index--] = elephents[dp[i][j]].ID;
		if (ans[i][j] == 1)
		{
			--i;
			--j;
		}
		else
		{
			--i;
		}
	}
	return res;
}