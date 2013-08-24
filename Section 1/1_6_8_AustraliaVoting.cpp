#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cassert>

using namespace std;

//#define _MY_DEBUG_

/*
	重定向输入输出流
	#define cin fin
	#define cout fout
*/


// 候选人最大数目
const int PEOPLE_NUM = 20;
// 最大行数
const int MAX_LINE = 1000;

// 候选人姓名数组
string names[PEOPLE_NUM];

// 选票
int vote[MAX_LINE][PEOPLE_NUM];

// 候选人数目
int numPeople;

// 选票数目
int voteNum = 0;

// 候选人的得票数
int peopleVoteNum[PEOPLE_NUM];

// 最差得票
int lastVoteNum[PEOPLE_NUM];

// 得票最多的人,不一定只有一个
int maxVotePeople[PEOPLE_NUM];

// 得票最少的人
int minVotePeople[PEOPLE_NUM];

// 每个选票情况的第一选择指针，默认都是第一个
int bestIndex[MAX_LINE];

// 剩余候选人人数
int lastPeople;

/*
	主函数
*/
void MainStructure();

/*
	处理过程
*/
void ProcessVoting();

/*
	判断是否结束，以及结束类型：是一个人还是多个人！
	如果是:maxNum中存放人数
*/
bool IsOK(int &maxNum);

/*
	统计每个人的得票数
*/
void StatisticVote();

/*
	统计得票最多的人
*/
void StaticMaxVote(int &maxNum);

/*
	统计得票最少的人
*/
void StaticMinVote(int &minNum);


/*
	去除得票最少的人
*/
void EraseMinPeople(int min);

/*
	重新统计得票情况
*/
void ReStatistic(int minNum);

/*
	判断num是否是被淘汰的人
*/
bool IsErased(int num, int minNum);


int main()
{
	//cout << "Test" << endl;

//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/110108.inp";
//
//	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
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
	// 所有的测试次数
	int count = 0;
	cin >> count;
	// 去除空行
	cin.get();
	cin.get();

	/*getchar();
	getchar();*/

	// 读入缓冲区
	char buf[256];

	while (count--)
	{
		cin >> numPeople;

		// 空白字符
		cin.get();
		//getchar();

		// 读入候选人姓名
		for (int i = 0; i < numPeople; ++i)
		{
			getline(cin, names[i]);
		}

		// 读入选票，如果不是空行，则读入
		//while (gets(buf))
		voteNum = 0;
		while (cin.getline(buf, sizeof(buf), '\n'))
		{
			// 如果是空行，终止
			if (buf[0] == '\0')
			{
				break;
			}
			// 解析字符串
			stringstream strStream(buf);
			for (int i = 0; i < numPeople; ++i)
			{
				strStream >> vote[voteNum][i];
				// 从0开始
				--vote[voteNum][i];
			}
			++voteNum;
		}
		// 处理
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
	// 剩余候选人数目
	lastPeople = numPeople;
	// 1.判断是否结束，以及结束类型：是一个人还是多个人！
	//int kind = 0;
	// 初始化bestIndex为0
	memset(bestIndex, 0, sizeof(bestIndex));
	// 2.统计每个人的得票情况
	StatisticVote();
	int maxNum = 0;
	while (!IsOK(maxNum))
	{
		// 3.统计得票最低的个数
		// 票数最少的人的个数
		int minNum;
		StaticMinVote(minNum);
		// 4.由于不满足条件，因此去除得票最少的候选人
		EraseMinPeople(minNum);

		// 5.重新统计得票情况
		ReStatistic(minNum);
	}
	for (int i = 0; i < maxNum; ++i)
	{
		cout << names[maxVotePeople[i]] << endl;
	}
}

bool IsOK(int &maxNum)
{
	// 得票最多的人个数
	maxNum = 0;
	StaticMaxVote(maxNum);
	// 如果只有一个人
	if (maxNum == 1)
	{
		// 判断得票数目是否大于50%
		int maxVote = peopleVoteNum[maxVotePeople[0]];
		//double half = (double)voteNum * 0.5;
		if (maxVote > voteNum / 2)
		{
			return true;
		}
	}
	else
	{ // 一定有得票最多的人.判断所有人是否得票数都一样
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
		// 统计第一得票数 
		// 第i张投票的第bestIndex选择：vote[i][bestIndex[i]		
		peopleVoteNum[vote[i][bestIndex[i]]]++;
		// 统计每个人的最后票:vote[i][numPeople - 1]
		lastVoteNum[vote[i][numPeople - 1]]++;
	}
}

void EraseMinPeople(int min)
{
	// 将得票最少的人除去
	lastPeople -= min;
	for (int i = 0; i < min; ++i)
	{
		// 得票数为0
		peopleVoteNum[minVotePeople[i]] = 0;
		// 最后一张也为0
		lastVoteNum[minVotePeople[i]] = 0;
	}
}

void ReStatistic(int minNum)
{
	// 重新统计第一选票的得票情况
	// 将所有选票的第一选票是被删除的情况的bestIndex++
	for (int i = 0; i < voteNum; ++i)
	{
		while (IsErased(vote[i][bestIndex[i]], minNum))
		{
			// 如果是被淘汰的，向后移动
			++bestIndex[i];
		}
	}
	memset(peopleVoteNum, 0, sizeof(peopleVoteNum));
	// 重新统计
	for (int i = 0; i < voteNum; ++i)
	{
		// 统计第一得票数 
		// 第i张投票的第bestIndex选择：vote[i][bestIndex[i]		
		peopleVoteNum[vote[i][bestIndex[i]]]++;	
	}
}

void StaticMaxVote(int &maxNum)
{
	maxNum = 0;
	// 1.找到第一张的票数最大
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
	// 1.找到最后一张的票数最大
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