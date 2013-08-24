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

const int MAX_INT = 0x1FFFFFFF;

// 路口数量
const int MAX_ROAD = 501;
// 消防栓数量
const int MAX_STATION = 101;

// 路口之间的边信息
int edge[MAX_ROAD][MAX_ROAD];

// 路口数量
int roadNum;

// 消防栓数量
int stationNum;

// 消防栓所在位置
int stationPos[MAX_STATION];

// 每一个路口是否有消防站
bool stationMap[MAX_ROAD];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	Floyd算法，计算各个节点到其他节点的距离
*/
void Floyd();

/*
	Solve
*/
int Solve();

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
		memset(stationMap, 0, sizeof(stationMap));

		cin >> stationNum >> roadNum;
		// 读取消防栓位置
		for (int i = 0; i < stationNum; ++i)
		{
			cin >> stationPos[i];
			// 设置在相应的路口有消防站
			stationMap[stationPos[i]] = true;
		}
		// 初始化边信息
		for (int i = 1; i <= roadNum; ++i)
		{
			for (int j = 1; j <= roadNum; ++j)
			{
				edge[i][j] = MAX_INT;
			}
		}
		// 读取路口边信息		
		string str;
		int n1, n2, dist;
		cin.ignore();
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			stringstream ss(str);
			ss >> n1 >> n2 >> dist;
			edge[n1][n2] = dist;
			edge[n2][n1] = dist;
		}
		// 初始化edge，每一条边到自己的距离为0
		for (int i = 1; i <= roadNum; ++i)
		{
			edge[i][i] = 0;
		}
		// 调用Floyd算法
		Floyd();
		cout << Solve() << endl;

		if (count)
		{
			cout << endl;
		}
	}
}

void Floyd()
{
	//for (int i = 1; i <= roadNum; ++i)
	//{
	//	for (int j = i + 1; j <= roadNum; ++j)
	//	{
	//		for (int k = 1; k <= i; ++k)
	//		{
	//			if (edge[i][j] + edge[j][k] < edge[i][k])
	//			{
	//				edge[i][k] = edge[i][j] + edge[j][k];
	//			}
	//		}
	//	}
	//}
	// 前k个节点，从i到j
	for (int k = 1; k <= roadNum; ++k)
	{
		for (int i = 1; i <= roadNum; ++i)
		{
			for (int j = 1; j <= roadNum; ++j)
			{
				int throughK = edge[i][k] + edge[k][j];
				if (throughK < edge[i][j])
				{
					edge[i][j] = throughK;
				}
			}
		}
	}
}

int Solve()
{
	int minDist = MAX_INT;
	int roadID = 0;

	//sort(stationPos, stationPos + stationNum);
	// 尝试遍历每一个路口
	for (int i = 1; i <= roadNum; ++i)
	{
		// 只有在没有的时候，才遍历
		if (!stationMap[i])
		{			
			// 在i处放置一个
			stationMap[i] = true;

			int curMin = 0;

			// 每一个路口，求能到达消防站的最小值
			for (int j = 1; j <= roadNum; ++j)
			{
				// 对于每一个路口来说
				int everyRoadMin = MAX_INT;
				for (int k = 1; k <= roadNum; ++k)
				{
					// 如果它是消防站
					if (stationMap[k])
					{
						if (edge[j][k] < everyRoadMin)
						{
							everyRoadMin = edge[j][k];
						}
					}
				}
				if (everyRoadMin > curMin)
				{
					curMin = everyRoadMin;
				}			
			}
			if (curMin < minDist)
			{
				minDist = curMin;
				roadID = i;
			}

			// 取消放置
			stationMap[i] = false;
		}
	}
	return roadID;
}