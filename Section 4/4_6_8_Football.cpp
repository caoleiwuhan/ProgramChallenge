#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <cassert>
#include <iomanip>
#include <map>
#include <cctype>

using namespace std;

#define _MY_DEBUG_

// Team结构
struct Team
{
	string name;		// 名字
	int rank;			// 排名
	int score;			// 得分

	int winCount;		// 胜场
	int drawCount;		// 平场
	int loseCount;		// 负场

	int kickBallNum;	// 进球数
	int loseBallNum;	// 失球数

	Team()
	{
		rank = 0;
		score = 0;

		winCount = 0;
		drawCount = 0;
		loseCount = 0;

		kickBallNum = 0;
		loseBallNum = 0;
	}
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
	排序
*/
bool TeamCompare(Team *t1, Team *t2);

/*
	StrToLower
*/
void StrtoUpper(string &str);

int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/1.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);
	//cout.rdbuf(fout.rdbuf());

#endif

	Process();
		
}

void Process()
{
	// 保存<str, team>
	map<string, Team> teamMap;
	// 保存数组
	vector<Team *> teamVec;

	// 测试数据组数
	int count;
	cin >> count;
	cin.get();
	while (count--)
	{
		// 联赛名
		string leagueName;
		getline(cin, leagueName);
		cout << leagueName << endl;

		teamMap.clear();
		teamVec.clear();
		// 球队数
		int clubNum;
		cin >> clubNum;
		cin.get();
		string clubName;
		for (int i = 0; i < clubNum; ++i)
		{			
			getline(cin, clubName);
			Team t;
			t.name = clubName;
			teamMap[clubName] = t;
			teamVec.push_back(&teamMap[clubName]);
		}
		int matchNum = 0;
		cin >> matchNum;
		cin.get();
		for (int i = 0; i < matchNum; ++i)
		{
			string matchInfo;
			getline(cin, matchInfo);
			// 解析matchInfo
			size_t pos = matchInfo.find('#');
			string name1 = matchInfo.substr(0, pos);
			matchInfo = matchInfo.substr(pos + 1);
			stringstream ss(matchInfo);

			int ball1, ball2;
			string name2;
			char rawCh;
			ss >> ball1 >> rawCh >> ball2;
			pos = matchInfo.find('#');
			name2 = matchInfo.substr(pos + 1);

			Team &t1 = teamMap[name1];
			Team &t2 = teamMap[name2];
			if (ball1 > ball2)
			{	// 胜
				t1.score += 3;
				++t1.winCount;
				++t2.loseCount;
			}
			else if (ball1 < ball2)
			{	// 负
				t2.score += 3;
				++t2.winCount;
				++t1.loseCount;
			}
			else
			{	// 平
				++t1.score;
				++t2.score;
				++t1.drawCount;
				++t2.drawCount;
			}
			t1.kickBallNum += ball1;
			t1.loseBallNum += ball2;
			t2.kickBallNum += ball2;
			t2.loseBallNum += ball1;
		}
		// 排序
		sort(teamVec.begin(), teamVec.end(), TeamCompare);

		for (int i = 1; i <= teamVec.size(); ++i)
		{
			Team *t = teamVec[i - 1];
			string str;
			stringstream ss(str);
			ss << i << ") " << t->name << " " << t->score << "p, " 
				<< (t->winCount + t->drawCount + t->loseCount) << "g (" 
				<< t->winCount << '-' << t->drawCount << '-' << t->loseCount << "), " 
				<< (t->kickBallNum - t->loseBallNum) << "gd (" 
				<< t->kickBallNum << '-' << t->loseBallNum << ")\n";
			cout << ss.str();
		}

		if (count)
		{
			cout << endl;
		}
	}
}

// 从大到小排序
bool TeamCompare(Team *t1, Team *t2)
{
	if (t1->score != t2->score)
	{	// 得分
		return t1->score > t2->score;
	}
	else if (t1->winCount != t2->winCount)
	{	// 获胜场次
		return t1->winCount > t2->winCount;
	}
	else if ((t1->kickBallNum - t1->loseBallNum) != 
				(t2->kickBallNum - t2->loseBallNum))
	{	// 净胜球
		return (t1->kickBallNum - t1->loseBallNum) > 
				(t2->kickBallNum - t2->loseBallNum);
	}
	else if (t1->kickBallNum != t2->kickBallNum)
	{	// 进球数
		return t1->kickBallNum > t2->kickBallNum;
	}
	else if ((t1->winCount + t1->drawCount + t1->loseCount) != 
			((t2->winCount + t2->drawCount + t2->loseCount)))
	{	// 比赛场数
		return (t1->winCount + t1->drawCount + t1->loseCount) < 
			((t2->winCount + t2->drawCount + t2->loseCount));
	}
	else
	{ // 大小写不敏感的字典序
		string name1 = t1->name;
		string name2 = t2->name;
		StrtoUpper(name1);
		StrtoUpper(name2);
		int res = strcmp(name1.c_str(), name2.c_str());
		return (res < 0);
		//return stricmp(name1.c_str(), name2.c_str()) < 0;
	}
}

void StrtoUpper(string &str)
{
	int len = str.length();
	for (int i = 0; i < len; ++i)
	{
		//if (isalpha(str[i]))
		{
			str[i] = toupper(str[i]);
		}
	}
}