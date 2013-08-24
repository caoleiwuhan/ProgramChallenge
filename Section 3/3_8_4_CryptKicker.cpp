#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>

using namespace std;

//#define _MY_DEBUG_

/*
	问题：题目很明确：只有字母的编码！！！
	没有考虑到字母对空格的情况！！！
*/

// 初始字符串
string initStr = "the quick brown fox jumps over the lazy dog";
//				  xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj

// 字母映射表：从a到z
char charMap[30];

// 保存所有的输入str
string crypts[110];

/*
	对于相同字母出现在不同位置的情况：必须在同样的位置出现！
*/

/*
	判断是否可以映射
		保证长度相同：map[i] = ch 表示第i(按字母序)个字母表示位ch
*/
bool IsMapOK(string str);


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
void Handle(string crypts[], int len);

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
	int count = 0;
	cin >> count;
	// 去除\n
	cin.get();
	int initStrLen = initStr.size();
	// 去除空行
	cin.get();
	while (count--)
	{
		string str;
		int index = 0;
		bool found = false;
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			crypts[index++] = str;
			if (!found && (str.length() == initStrLen))
			{
				if (IsMapOK(str))
				{
					found = true;
				}
			}
		}
		if (found)
		{
			Handle(crypts, index);
		}
		else
		{
			cout << "No solution." << endl;
		}
		if (count)
		{
			cout << endl;
		}
	}
}

// 默认是小写
bool IsMapOK(string str)
{
	int len = str.size();

	memset(charMap, 0, sizeof(charMap));
	
	for (int i = 0; i < len; ++i)
	{
		char ch = str[i];
		if (isalpha(ch))
		{
			int index = ch - 'a';
			if (charMap[index] != 0)
			{
				// 已经映射过
				if (charMap[index] != initStr[i])
				{
					return false;
				}
			}
			else
			{
				// 字符对应的必须是字符，空格对应的必须是空格
				if (!isalpha(initStr[i]))
				{
					return false;
				}
				charMap[index] = initStr[i];
			}
		}
		else
		{ // 必须都不是字符
			if (isalpha(initStr[i]))
			{
				return false;
			}			
		}
	}
	for (int i = 0; i < 26; ++i)
	{
		if (charMap[i] == 0)
		{
			return false;
		}
	}
	return true;
}

void Handle(string crypts[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		string str = crypts[i];
		int strSize = str.length();
		for (int j = 0; j < strSize; ++j)
		{
			char ch = str[j];
			if (islower(ch))
			{
				cout << charMap[ch - 'a'];
			}
			else
			{
				cout << ch;
			}
		}
		cout << endl;
	}
}