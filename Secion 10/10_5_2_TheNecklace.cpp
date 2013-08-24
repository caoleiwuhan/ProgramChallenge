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

struct Node
{
	int id;		// 珠子编号
	bool left;	// 是否是左侧

	Node(int _id, bool _left) : id(_id), left(_left) 
	{}
};


const int MAXV = 1001;

// 珠子的个数
int headNum;

// 颜色
int color[MAXV][2];

// 长度为len的串有多个，因此用vector
map<int, vector< list<Node> > > nodeMap;

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP();

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
		cin >> headNum;
		for (int i = 0; i < headNum; ++i)
		{
			cin >> color[i][0] >> color[i][1];
		}
		memset(a, 0, sizeof(a));
		if (count)
		{
			cout << endl;
		}
	}
}

void DP()
{
	nodeMap.clear();
	// 初始化,长度为1的
	vector<list<Node> > vListNode1;
	for (int i = 0; i < headNum; ++i)
	{
		// 左面
		Node n1(i, true);
		list<Node> list1;
		list1.push_back(n1);
		vListNode1.push_back(list1);

		// 右面
		Node n2(i, true);
		list<Node> list2;
		list2.push_back(n2);
		vListNode1.push_back(list2);
	}
	nodeMap[1] = vListNode1;

	// 从1到headNum-1，向上计算
	for (int i = 1; i < headNum - 1; ++i)
	{
		// 从map中取出长度为i的list
		vector<list<Node> > vecListNode = nodeMap[i];
		int size = vecListNode.size();
		for (int j = 0; j < size; ++j)
		{
			list<Node> listNode = vecListNode[j];
			// 遍历list
			bool bInList[MAXV] = {false};
			for (list<Node>::iterator itr = listNode.begin(); itr != listNode.end(); ++itr)
			{
				bInList[itr->id] = true;
			}
			// 只考虑不在里面的
			for (list<Node>::iterator itr = listNode.begin(); itr != listNode.end(); ++itr)
			{
				for (int s = 0; s < headNum; ++s)
				{
					// 如果没在list中
					if (!bInList[s])
					{
						

					}
				}
			}
		}
	}
}