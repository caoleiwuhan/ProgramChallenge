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

//#define _MY_DEBUG_

const int MAXV = 25001;
const int MAXDEGREE = 101;

bool processed[MAXV];
bool discovered[MAXV];
int parent[MAXV];

// 最长
int longest = 0;

void dfs(string word, int cur);

void dfsHelp(string str, int cur);

// 字典
string words[MAXV];
map<string, int> wordMap;


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();




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
	string str;
	while (cin >> str)
	{
		words[count++] = str;
		wordMap[str] = 0;
	}
	for (map<string, int>::iterator itr = wordMap.begin(); itr != wordMap.end(); ++itr)
	{
		for (map<string, int>::iterator itr2 = wordMap.begin(); itr2 != wordMap.end(); ++itr2)
		{
			itr2->second = 0;
		}
		
		itr->second = 1;
		dfs(itr->first, 1);		
	}
	cout << longest << endl;
	//sort(words, words + count);	
}

void dfs(string word, int cur)
{
	if (cur > longest)
	{
		longest = cur;
	}
	// 增加、删除、改变：
	int length = word.length();
	for (int i = 0; i < length; ++i)
	{
		string str;
		for (char ch = 'a'; ch <= 'z'; ++ch)
		{			
			// 增加
			str = word;
			str.insert(i, 1, ch);
			dfsHelp(str, cur);

			// 替换
			str = word;
			str[i] = ch;
			dfsHelp(str, cur);
		}
		// 删除
		str = word;
		str.erase(i, 1);
		dfsHelp(str, cur);
	}	
}

void dfsHelp(string str, int cur)
{
	// 如果str在字典中
	map<string, int>::iterator itr = wordMap.find(str);
	if (itr != wordMap.end())
	{
		// 如果没有处理过
		if (itr->second == 0)
		{
			itr->second = 1;
			dfs(str, cur + 1);
		}
	}
}


