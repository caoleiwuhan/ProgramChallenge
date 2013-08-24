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

// ·������
const int MAX_ROAD = 501;
// ����˨����
const int MAX_STATION = 101;

// ·��֮��ı���Ϣ
int edge[MAX_ROAD][MAX_ROAD];

// ·������
int roadNum;

// ����˨����
int stationNum;

// ����˨����λ��
int stationPos[MAX_STATION];

// ÿһ��·���Ƿ�������վ
bool stationMap[MAX_ROAD];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	Floyd�㷨����������ڵ㵽�����ڵ�ľ���
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
		memset(stationMap, 0, sizeof(stationMap));

		cin >> stationNum >> roadNum;
		// ��ȡ����˨λ��
		for (int i = 0; i < stationNum; ++i)
		{
			cin >> stationPos[i];
			// ��������Ӧ��·��������վ
			stationMap[stationPos[i]] = true;
		}
		// ��ʼ������Ϣ
		for (int i = 1; i <= roadNum; ++i)
		{
			for (int j = 1; j <= roadNum; ++j)
			{
				edge[i][j] = MAX_INT;
			}
		}
		// ��ȡ·�ڱ���Ϣ		
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
		// ��ʼ��edge��ÿһ���ߵ��Լ��ľ���Ϊ0
		for (int i = 1; i <= roadNum; ++i)
		{
			edge[i][i] = 0;
		}
		// ����Floyd�㷨
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
	// ǰk���ڵ㣬��i��j
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
	// ���Ա���ÿһ��·��
	for (int i = 1; i <= roadNum; ++i)
	{
		// ֻ����û�е�ʱ�򣬲ű���
		if (!stationMap[i])
		{			
			// ��i������һ��
			stationMap[i] = true;

			int curMin = 0;

			// ÿһ��·�ڣ����ܵ�������վ����Сֵ
			for (int j = 1; j <= roadNum; ++j)
			{
				// ����ÿһ��·����˵
				int everyRoadMin = MAX_INT;
				for (int k = 1; k <= roadNum; ++k)
				{
					// �����������վ
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

			// ȡ������
			stationMap[i] = false;
		}
	}
	return roadID;
}