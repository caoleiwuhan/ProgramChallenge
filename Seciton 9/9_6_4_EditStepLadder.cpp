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

// �
int longest = 0;

void dfs(string word, int cur);

void dfsHelp(string str, int cur);

// �ֵ�
string words[MAXV];
map<string, int> wordMap;


/*
	MainStructure: ���ṹ
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
	// ���ӡ�ɾ�����ı䣺
	int length = word.length();
	for (int i = 0; i < length; ++i)
	{
		string str;
		for (char ch = 'a'; ch <= 'z'; ++ch)
		{			
			// ����
			str = word;
			str.insert(i, 1, ch);
			dfsHelp(str, cur);

			// �滻
			str = word;
			str[i] = ch;
			dfsHelp(str, cur);
		}
		// ɾ��
		str = word;
		str.erase(i, 1);
		dfsHelp(str, cur);
	}	
}

void dfsHelp(string str, int cur)
{
	// ���str���ֵ���
	map<string, int>::iterator itr = wordMap.find(str);
	if (itr != wordMap.end())
	{
		// ���û�д����
		if (itr->second == 0)
		{
			itr->second = 1;
			dfs(str, cur + 1);
		}
	}
}


