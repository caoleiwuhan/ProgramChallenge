#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

#define _MY_DEBUG_

// 队伍数：100

// listNode 数据结构：
struct ListNode
{
	int teamID;		// 队伍
	int problemID;	// 题目
	int time;		// 罚时
	char state;		// 状态：C、I

	ListNode() : teamID(0), problemID(0), time(0), state('A'){}
};

// vecNode
struct VecNode
{
	int teamID;		// 队伍
	int solved;		// 已解决问题数
	int time;		// 罚时

	VecNode() : teamID(-1), solved(0), time(0) {}
};


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Handle：处理每一组中的每一个实例
*/
void Handle(map<int, list<ListNode> *>& listNodeMap);

/*
	排序函数
*/
bool MyCompare(VecNode *left, VecNode *right);



int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110207.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	//fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
	Process();

#endif
		
}

void Process()
{
	// 测试数据组数
	int count = 0;
	cin >> count;

	string str;
	// 去除空行
	cin.get();
	cin.get();
	//getline(cin, str);

	while (count--)
	{
		// 处理一组数据，存放句柄:list<ListNode>
		map<int, list<ListNode> *> listNodeMap;
		
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			// 解析str
			ListNode node;
			stringstream ss(str);
			ss >> node.teamID >> node.problemID >> node.time >> node.state;
			// 如果以teamID为key的map为null，则需要新建
			map<int, list<ListNode> *>::iterator mapItr = listNodeMap.find(node.teamID);
			if (mapItr == listNodeMap.end())
			{
				// 结束的时候要delete
				list<ListNode> *pNodeLists = new list<ListNode>();
				pNodeLists->push_back(node);
				listNodeMap[node.teamID] = pNodeLists;
			}
			else
			{
				list<ListNode> *pList = (*mapItr).second;
				// 如果已经找到
				//(*mapItr).second->push_back(node);
				// 如果已经解决的问题，看是否已经解决过，且时间更短
				// 正确之后再提交的就不管了？
				bool isInsert = true;
				for (list<ListNode>::iterator pItr = pList->begin(); pItr != pList->end(); ++pItr)
				{
					ListNode &pNode = (*pItr);
					if ((pNode.teamID == node.teamID) &&
						(pNode.problemID == node.problemID))
					{
						// 如果已经提交的答案中有正确答案，则相同题号、相同队伍的不再管！
						if (pNode.state == 'C')
						{							
							isInsert = false;
							break;							
						}						
					}						
				}
				if (isInsert)
				{
					(*mapItr).second->push_back(node);
				}
			}
		}
		Handle(listNodeMap);

		// delete
		for (map<int, list<ListNode> *>::iterator itr = listNodeMap.begin(); itr != listNodeMap.end(); ++itr)
		{
			delete (itr->second);
		}
		if (count)
		{
			cout << endl;
		}
	}
}

void Handle(map<int, list<ListNode> *>& listNodeMap)
{	
	// 计算过程：
	// 1.建立size个vectorNode
	vector<VecNode *> teamVec(listNodeMap.size());
	int size = listNodeMap.size();
	// 初始化
	for (int i = 0; i < size; ++i)
	{
		VecNode *pVecNode = new VecNode();
		teamVec[i] = (pVecNode);
	}
	int index = 0;
	// 2.遍历map，计算vec
	for (map<int, list<ListNode> *>::iterator mapItr = listNodeMap.begin(); mapItr != listNodeMap.end(); ++mapItr)
	{
		// 
		list<ListNode> * pListNode = mapItr->second;
		teamVec[index]->teamID = mapItr->first;
		// 解决的问题的set
		set<int> solvedSet;
		// 遍历listNode, 得到解答的问题编号
		for (list<ListNode>::iterator listItr = pListNode->begin(); listItr != pListNode->end(); ++listItr)
		{
			if (listItr->state == 'C')
			{
				solvedSet.insert(listItr->problemID);
				teamVec[index]->time += listItr->time;	
			}				
		}
		// 复制解决问题数目
		teamVec[index]->solved = solvedSet.size();

		for (list<ListNode>::iterator listItr = pListNode->begin(); listItr != pListNode->end(); ++listItr)
		{
			if (listItr->state == 'I')
			{
				// 已经解决，因此要罚时20
				if (solvedSet.find(listItr->problemID) != solvedSet.end())
				{
					teamVec[index]->time += 20;
				}
			}				
		}
		++index;
	}
	// 3.排序: 问题数：罚时数：序号
	sort(teamVec.begin(), teamVec.end(), MyCompare);

	// 4.输出
	for (int i = 0; i < size; ++i)
	{
		VecNode *pVecNode = teamVec[i];
		cout << pVecNode->teamID << " " << pVecNode->solved << " " << pVecNode->time << endl;
	}

	// delete
	for (int i = 0; i < size; ++i)
	{		
		delete teamVec[i];
	}
}

// 排序: 问题数：罚时数：序号
bool MyCompare(VecNode *left, VecNode *right)
{
	if (left->solved > right->solved)
	{
		return true;
	}
	else if (left->solved < right->solved)
	{
		return false;
	}
	else if (left->time < right->time)
	{ // left->solved == right->solved
		return true;
	}
	else if (left->time > right->time)
	{
		return false;
	}
	else
	{ // left->time == right->time
		return (left->teamID < right->teamID);
	}
}
