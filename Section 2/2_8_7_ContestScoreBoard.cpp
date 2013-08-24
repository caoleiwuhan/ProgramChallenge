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

// ��������100

// listNode ���ݽṹ��
struct ListNode
{
	int teamID;		// ����
	int problemID;	// ��Ŀ
	int time;		// ��ʱ
	char state;		// ״̬��C��I

	ListNode() : teamID(0), problemID(0), time(0), state('A'){}
};

// vecNode
struct VecNode
{
	int teamID;		// ����
	int solved;		// �ѽ��������
	int time;		// ��ʱ

	VecNode() : teamID(-1), solved(0), time(0) {}
};


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	Handle������ÿһ���е�ÿһ��ʵ��
*/
void Handle(map<int, list<ListNode> *>& listNodeMap);

/*
	������
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110207.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
	// ������������
	int count = 0;
	cin >> count;

	string str;
	// ȥ������
	cin.get();
	cin.get();
	//getline(cin, str);

	while (count--)
	{
		// ����һ�����ݣ���ž��:list<ListNode>
		map<int, list<ListNode> *> listNodeMap;
		
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			// ����str
			ListNode node;
			stringstream ss(str);
			ss >> node.teamID >> node.problemID >> node.time >> node.state;
			// �����teamIDΪkey��mapΪnull������Ҫ�½�
			map<int, list<ListNode> *>::iterator mapItr = listNodeMap.find(node.teamID);
			if (mapItr == listNodeMap.end())
			{
				// ������ʱ��Ҫdelete
				list<ListNode> *pNodeLists = new list<ListNode>();
				pNodeLists->push_back(node);
				listNodeMap[node.teamID] = pNodeLists;
			}
			else
			{
				list<ListNode> *pList = (*mapItr).second;
				// ����Ѿ��ҵ�
				//(*mapItr).second->push_back(node);
				// ����Ѿ���������⣬���Ƿ��Ѿ����������ʱ�����
				// ��ȷ֮�����ύ�ľͲ����ˣ�
				bool isInsert = true;
				for (list<ListNode>::iterator pItr = pList->begin(); pItr != pList->end(); ++pItr)
				{
					ListNode &pNode = (*pItr);
					if ((pNode.teamID == node.teamID) &&
						(pNode.problemID == node.problemID))
					{
						// ����Ѿ��ύ�Ĵ�������ȷ�𰸣�����ͬ��š���ͬ����Ĳ��ٹܣ�
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
	// ������̣�
	// 1.����size��vectorNode
	vector<VecNode *> teamVec(listNodeMap.size());
	int size = listNodeMap.size();
	// ��ʼ��
	for (int i = 0; i < size; ++i)
	{
		VecNode *pVecNode = new VecNode();
		teamVec[i] = (pVecNode);
	}
	int index = 0;
	// 2.����map������vec
	for (map<int, list<ListNode> *>::iterator mapItr = listNodeMap.begin(); mapItr != listNodeMap.end(); ++mapItr)
	{
		// 
		list<ListNode> * pListNode = mapItr->second;
		teamVec[index]->teamID = mapItr->first;
		// ����������set
		set<int> solvedSet;
		// ����listNode, �õ�����������
		for (list<ListNode>::iterator listItr = pListNode->begin(); listItr != pListNode->end(); ++listItr)
		{
			if (listItr->state == 'C')
			{
				solvedSet.insert(listItr->problemID);
				teamVec[index]->time += listItr->time;	
			}				
		}
		// ���ƽ��������Ŀ
		teamVec[index]->solved = solvedSet.size();

		for (list<ListNode>::iterator listItr = pListNode->begin(); listItr != pListNode->end(); ++listItr)
		{
			if (listItr->state == 'I')
			{
				// �Ѿ���������Ҫ��ʱ20
				if (solvedSet.find(listItr->problemID) != solvedSet.end())
				{
					teamVec[index]->time += 20;
				}
			}				
		}
		++index;
	}
	// 3.����: ����������ʱ�������
	sort(teamVec.begin(), teamVec.end(), MyCompare);

	// 4.���
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

// ����: ����������ʱ�������
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
