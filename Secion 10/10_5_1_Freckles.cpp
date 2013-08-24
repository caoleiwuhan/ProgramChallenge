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

const int MAXV = 101;

const int MAX_NUM = 0x7FFFFFFF;

double minDist[MAXV];
int parent[MAXV];
bool mapPos[MAXV];

double pos[MAXV][2];

double dist[MAXV][MAXV];

int numPos;


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	���������֮��ľ���
*/
void CalDist();

/*
	Prim
*/
double Prim();

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
	double pX, pY;
	while (count--)
	{
		cin >> numPos;
		for (int i = 0; i < numPos; ++i)
		{
			cin >> pos[i][0] >> pos[i][1];
		}
		CalDist();
		double ans = Prim();
		cout << fixed << setprecision(2) << ans << endl;

		if (count)
		{
			cout << endl;
		}
	}
	
}

void CalDist()
{
	for (int i = 0; i < numPos; ++i)
	{
		for (int j = 0; j < numPos; ++j)
		{
			if (i == j)
			{
				dist[i][j] = 0;
			}
			else
			{
				dist[i][j] = sqrt(pow(pos[i][0] - pos[j][0], 2) + 
					pow(pos[i][1] - pos[j][1], 2));
			}
		}
	}
}

double Prim()
{
	memset(mapPos, 0, sizeof(mapPos));
	for (int i = 0; i < numPos; ++i)
	{
		minDist[i] = MAX_NUM;
	}

	// ��0��ʼ
	int v = 0;
	double ans = 0;
	minDist[v] = 0;
	parent[v] = -1;

	while (!mapPos[v])
	{
		mapPos[v] = true;

		// ������v������
		for (int i = 0; i < numPos; ++i)
		{
			if (mapPos[i])
			{
				continue;
			}
			double tmpDist = dist[v][i];
			if (tmpDist < minDist[i])
			{
				minDist[i] = tmpDist;
				parent[i] = v;
			}
		}

		v = 0;
		double min = MAX_NUM;
		// Ѱ����С��
		for (int i = 0; i < numPos; ++i)
		{
			if (!mapPos[i] && (minDist[i] < min))
			{
				v = i;
				min = minDist[i];
			}
		}
		ans += minDist[v];
	}

	return ans;
}