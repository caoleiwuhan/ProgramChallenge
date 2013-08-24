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

const int MAXV = 60;

struct Node
{
	int nT;
	int towers[MAXV];
	Node()
	{		
		memset(towers, 0, sizeof(towers));
	}
};

struct NodeCmp
{
	bool operator()(const Node &na, const Node &nb)
	{
		return (na.nT < nb.nT);
	}
};


// ��������
int nTower = 0;

// ���
int ans = 0;

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	curNum:��ǰ���ڴ������
	curTower:��ǰ�Ѿ�ʹ�õ�������
*/
void dfs(int curNum, int curTower);

/*
	�ж��Ƿ������
		�����Ѿ����꣬�Ҳ�������Ҫ��
*/
bool IsFinished(int curNum, int curTower);

/*
	�ж�һ�����Ƿ�����ȫƽ��
*/	
bool IsNumSqrt(int num);


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
		cin >> nTower;
		memset(towers, 0, sizeof(towers));
		ans = 0;
		dfs(1, 0);
		cout << ans << endl;
	}
}

void dfs(int nTower)
{
	// int:��Ҫ��������
	// �ֲ����
	priority_queue<Node, list<Node>, NodeCmp> q;

	Node a;
	q.push(a);
	int curNum = 1;
	
	while (!q.empty())
	{
		Node tmpNode = q.top();
		q.pop();
		if (IsFinished(curNum, tmpNode.nT))
		{
			if (curNum > ans)
			{
				ans = curNum;
			}
		}
		else
		{ // 
			for (int i = 0; i < tmpNode.nT; ++i)
			{
				int curTmp = tmpNode.towers[i];
				if (IsNumSqrt(curTmp + curNum))
				{
					tmpNode.towers[i] = curNum;
					q.push(tmpNode);
				}		
			}
			if (tmpNode.nT < nTower)
			{
				tmpNode.towers[tmpNode.nT] = curNum;
				dfs(curNum + 1, curTower + 1);
			}
		}
	}
	// �����ŵ�һ���µ�tower��
	if (curTower < nTower)
	{
		towers[curTower] = curNum;
		dfs(curNum + 1, curTower + 1);
	}
}

bool IsFinished(int curNum, int curTower)
{
	if (curTower < nTower)
	{
		return false;
	}
	for (int i = 0; i < curTower; ++i)
	{
		if (IsNumSqrt(towers[i] + curNum))
		{
			return false;
		}
	}
	return true;
}

bool IsNumSqrt(int num)
{
	int s = sqrt(double(num));
	if (s * s == num)
	{
		return true;
	}
	return false;
}
