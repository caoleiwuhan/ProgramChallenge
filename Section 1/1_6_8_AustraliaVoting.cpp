#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cassert>

using namespace std;

//#define _MY_DEBUG_

/*
	�ض������������
	#define cin fin
	#define cout fout
*/


// ��ѡ�������Ŀ
const int PEOPLE_NUM = 20;
// �������
const int MAX_LINE = 1000;

// ��ѡ����������
string names[PEOPLE_NUM];

// ѡƱ
int vote[MAX_LINE][PEOPLE_NUM];

// ��ѡ����Ŀ
int numPeople;

// ѡƱ��Ŀ
int voteNum = 0;

// ��ѡ�˵ĵ�Ʊ��
int peopleVoteNum[PEOPLE_NUM];

// ����Ʊ
int lastVoteNum[PEOPLE_NUM];

// ��Ʊ������,��һ��ֻ��һ��
int maxVotePeople[PEOPLE_NUM];

// ��Ʊ���ٵ���
int minVotePeople[PEOPLE_NUM];

// ÿ��ѡƱ����ĵ�һѡ��ָ�룬Ĭ�϶��ǵ�һ��
int bestIndex[MAX_LINE];

// ʣ���ѡ������
int lastPeople;

/*
	������
*/
void MainStructure();

/*
	�������
*/
void ProcessVoting();

/*
	�ж��Ƿ�������Լ��������ͣ���һ���˻��Ƕ���ˣ�
	�����:maxNum�д������
*/
bool IsOK(int &maxNum);

/*
	ͳ��ÿ���˵ĵ�Ʊ��
*/
void StatisticVote();

/*
	ͳ�Ƶ�Ʊ������
*/
void StaticMaxVote(int &maxNum);

/*
	ͳ�Ƶ�Ʊ���ٵ���
*/
void StaticMinVote(int &minNum);


/*
	ȥ����Ʊ���ٵ���
*/
void EraseMinPeople(int min);

/*
	����ͳ�Ƶ�Ʊ���
*/
void ReStatistic(int minNum);

/*
	�ж�num�Ƿ��Ǳ���̭����
*/
bool IsErased(int num, int minNum);


int main()
{
	//cout << "Test" << endl;

//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/110108.inp";
//
//	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
//	ifstream fin;
//	fin.open(inputStr);	
//	assert(fin.is_open());
//	cin.rdbuf(fin.rdbuf());	
//
//	ofstream fout;
//	fout.open(outputStr);
//	assert(fout.is_open());
//	cout.rdbuf(fout.rdbuf());
//
//#endif

	MainStructure();
	return 0;
}

void MainStructure()
{
	// ���еĲ��Դ���
	int count = 0;
	cin >> count;
	// ȥ������
	cin.get();
	cin.get();

	/*getchar();
	getchar();*/

	// ���뻺����
	char buf[256];

	while (count--)
	{
		cin >> numPeople;

		// �հ��ַ�
		cin.get();
		//getchar();

		// �����ѡ������
		for (int i = 0; i < numPeople; ++i)
		{
			getline(cin, names[i]);
		}

		// ����ѡƱ��������ǿ��У������
		//while (gets(buf))
		voteNum = 0;
		while (cin.getline(buf, sizeof(buf), '\n'))
		{
			// ����ǿ��У���ֹ
			if (buf[0] == '\0')
			{
				break;
			}
			// �����ַ���
			stringstream strStream(buf);
			for (int i = 0; i < numPeople; ++i)
			{
				strStream >> vote[voteNum][i];
				// ��0��ʼ
				--vote[voteNum][i];
			}
			++voteNum;
		}
		// ����
		ProcessVoting();
		if (count)
		{
			cout << endl;
		}
		//cin.get();
		//cin.get();
	}
}

void ProcessVoting()
{
	// ʣ���ѡ����Ŀ
	lastPeople = numPeople;
	// 1.�ж��Ƿ�������Լ��������ͣ���һ���˻��Ƕ���ˣ�
	//int kind = 0;
	// ��ʼ��bestIndexΪ0
	memset(bestIndex, 0, sizeof(bestIndex));
	// 2.ͳ��ÿ���˵ĵ�Ʊ���
	StatisticVote();
	int maxNum = 0;
	while (!IsOK(maxNum))
	{
		// 3.ͳ�Ƶ�Ʊ��͵ĸ���
		// Ʊ�����ٵ��˵ĸ���
		int minNum;
		StaticMinVote(minNum);
		// 4.���ڲ��������������ȥ����Ʊ���ٵĺ�ѡ��
		EraseMinPeople(minNum);

		// 5.����ͳ�Ƶ�Ʊ���
		ReStatistic(minNum);
	}
	for (int i = 0; i < maxNum; ++i)
	{
		cout << names[maxVotePeople[i]] << endl;
	}
}

bool IsOK(int &maxNum)
{
	// ��Ʊ�����˸���
	maxNum = 0;
	StaticMaxVote(maxNum);
	// ���ֻ��һ����
	if (maxNum == 1)
	{
		// �жϵ�Ʊ��Ŀ�Ƿ����50%
		int maxVote = peopleVoteNum[maxVotePeople[0]];
		//double half = (double)voteNum * 0.5;
		if (maxVote > voteNum / 2)
		{
			return true;
		}
	}
	else
	{ // һ���е�Ʊ������.�ж��������Ƿ��Ʊ����һ��
		if (maxNum == lastPeople)
		{		
			return true;
		}
	}
	return false;		 
}

void StatisticVote()
{	
	memset(peopleVoteNum, 0, sizeof(peopleVoteNum));
	memset(lastVoteNum, 0, sizeof(lastVoteNum));
	for (int i = 0; i < voteNum; ++i)
	{
		// ͳ�Ƶ�һ��Ʊ�� 
		// ��i��ͶƱ�ĵ�bestIndexѡ��vote[i][bestIndex[i]		
		peopleVoteNum[vote[i][bestIndex[i]]]++;
		// ͳ��ÿ���˵����Ʊ:vote[i][numPeople - 1]
		lastVoteNum[vote[i][numPeople - 1]]++;
	}
}

void EraseMinPeople(int min)
{
	// ����Ʊ���ٵ��˳�ȥ
	lastPeople -= min;
	for (int i = 0; i < min; ++i)
	{
		// ��Ʊ��Ϊ0
		peopleVoteNum[minVotePeople[i]] = 0;
		// ���һ��ҲΪ0
		lastVoteNum[minVotePeople[i]] = 0;
	}
}

void ReStatistic(int minNum)
{
	// ����ͳ�Ƶ�һѡƱ�ĵ�Ʊ���
	// ������ѡƱ�ĵ�һѡƱ�Ǳ�ɾ���������bestIndex++
	for (int i = 0; i < voteNum; ++i)
	{
		while (IsErased(vote[i][bestIndex[i]], minNum))
		{
			// ����Ǳ���̭�ģ�����ƶ�
			++bestIndex[i];
		}
	}
	memset(peopleVoteNum, 0, sizeof(peopleVoteNum));
	// ����ͳ��
	for (int i = 0; i < voteNum; ++i)
	{
		// ͳ�Ƶ�һ��Ʊ�� 
		// ��i��ͶƱ�ĵ�bestIndexѡ��vote[i][bestIndex[i]		
		peopleVoteNum[vote[i][bestIndex[i]]]++;	
	}
}

void StaticMaxVote(int &maxNum)
{
	maxNum = 0;
	// 1.�ҵ���һ�ŵ�Ʊ�����
	int maxVote = 0;
	for (int i = 0; i < numPeople; ++i)
	{
		if (peopleVoteNum[i] > maxVote)
		{
			maxVote = peopleVoteNum[i];
		}
	}
	for (int i = 0; i < numPeople; ++i)
	{
		if (peopleVoteNum[i] == maxVote)
		{
			maxVotePeople[maxNum++] = i;
		}
	}
}

void StaticMinVote(int &minNum)
{
	minNum = 0;
	// 1.�ҵ����һ�ŵ�Ʊ�����
	int minVote = 0;
	for (int i = 0; i < numPeople; ++i)
	{
		if (lastVoteNum[i] > minVote)
		{
			minVote = lastVoteNum[i];
		}
	}
	for (int i = 0; i < numPeople; ++i)
	{
		if (lastVoteNum[i] == minVote)
		{
			minVotePeople[minNum++] = i;
		}
	}
}

bool IsErased(int num, int minNum)
{
	for (int i = 0; i < minNum; ++i)
	{
		if (num == minVotePeople[i])
		{
			return true;
		}
	}
	return false;
}