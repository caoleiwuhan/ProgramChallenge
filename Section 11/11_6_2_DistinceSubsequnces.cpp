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

int s[10001][101];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

int DP(string str1, string str2);


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
		string str1;
		string str2;
		cin >> str1 >> str2;
		cout << DP(str1, str2) << endl;
	}
}

int DP(string str1, string str2)
{
	int ans = 0;
	memset(s, 0, sizeof(s));
	int len1 = str1.length();
	int len2 = str2.length();
	/*if ((str1[i-1] == str2[j-1]) && (s[i-1][j-1] + 1) > tmp)
	{
		tmp = s[i-1][j-1];
	}*/
	for (int i = 1; i <= len1; ++i)
	{
		for (int j = 1; j <= (i < len2 ? i : len2); ++j)
		{
			int tmp = s[i-1][j];
			if (str1[i-1] == str2[j-1])
			{
				tmp += s[i-1][j-1];
				if (s[i-1][j-1] == 0)
				{
					// 如果是从第一个开始的
					if (j == 1)
					{
						tmp += 1;
					}
				}
			}

			s[i][j] = tmp;
		}
	}
	//for (int i = len2; i <= len1; ++i)
	//{
	//	if (s[i][len2] > ans)
	//	{
	//		ans = s[i][len2];
	//	}
	//}

	return s[len1][len2];
}