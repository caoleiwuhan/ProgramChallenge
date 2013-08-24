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
	int id;		// ���ӱ��
	bool left;	// �Ƿ������

	Node(int _id, bool _left) : id(_id), left(_left) 
	{}
};


const int MAXV = 1001;

// ���ӵĸ���
int headNum;

// ��ɫ
int color[MAXV][2];

// ����Ϊlen�Ĵ��ж���������vector
map<int, vector< list<Node> > > nodeMap;

/*
	MainStructure: ���ṹ
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
	// ��ʼ��,����Ϊ1��
	vector<list<Node> > vListNode1;
	for (int i = 0; i < headNum; ++i)
	{
		// ����
		Node n1(i, true);
		list<Node> list1;
		list1.push_back(n1);
		vListNode1.push_back(list1);

		// ����
		Node n2(i, true);
		list<Node> list2;
		list2.push_back(n2);
		vListNode1.push_back(list2);
	}
	nodeMap[1] = vListNode1;

	// ��1��headNum-1�����ϼ���
	for (int i = 1; i < headNum - 1; ++i)
	{
		// ��map��ȡ������Ϊi��list
		vector<list<Node> > vecListNode = nodeMap[i];
		int size = vecListNode.size();
		for (int j = 0; j < size; ++j)
		{
			list<Node> listNode = vecListNode[j];
			// ����list
			bool bInList[MAXV] = {false};
			for (list<Node>::iterator itr = listNode.begin(); itr != listNode.end(); ++itr)
			{
				bInList[itr->id] = true;
			}
			// ֻ���ǲ��������
			for (list<Node>::iterator itr = listNode.begin(); itr != listNode.end(); ++itr)
			{
				for (int s = 0; s < headNum; ++s)
				{
					// ���û��list��
					if (!bInList[s])
					{
						

					}
				}
			}
		}
	}
}