#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

//#define _MY_DEBUG_


// 保存文件
string files[300];
// 保存文件长度

// 保存文件索引
int arr1[300];
int arr2[300];

// bool：表示是否用过
bool IsUsed[300];

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
void Handle(int index);

/*
	排序函数
*/
bool StrLenCompareFunc(const string &str1, const string str2);

/*
	传入文件str，看是否满足
*/
bool IsSatisfy(string str, int index);

/*
	传入str、arr、arrSize，是否匹配
*/
bool IsMatch(string str, int arr[], int size);


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
	// 行尾
	// 空行
	cin.get();
	cin.get();
	while (count--)
	{
		string str;
		int index = 0;
		// getline把\n\r都吃掉了
		while (getline(cin, str))
		{
			if (str == "")
			{
				break;
			}
			files[index++] = str;
		}
		Handle(index);

		if (count)
		{
			cout << endl;
		}
	}
}

void Handle(int index)
{	
	// 1.按照文件长度由小到大排序
	sort(files, files + index, StrLenCompareFunc);
	// 方案1：
	// 不一定是第一个跟最后一个匹配！！！
	int shortLen = files[0].length();
	int start = 1;
	while (start < index && files[start].length() == shortLen)
	{
		++start;
	}
	
	// 并非所有的都相等
	if (start != index)
	{
		for (int i = 0; i <= start; ++i)
		{			
			// 将i与j相结合
			swap(files[0], files[i]);

			string str1 = files[0];
			str1 += files[index - 1];
			// 判断方案一是否可以
			bool isOK = IsSatisfy(str1, index);
			if (isOK)
			{
				cout << str1 << endl;
				return;
			}
			else
			{
				string str2 = files[index - 1];
				str2 += files[0];
				if (IsSatisfy(str2, index))
				{
					cout << str2 << endl;
					return;
				}
			}
			swap(files[0], files[i]);			
		}
	}
	else
	{
		for (int i = 0; i < start - 1; ++i)
		{
			for (int j = i + 1; j < start; ++j)
			{
				// 将i与j相结合
				swap(files[0], files[i]);
				swap(files[j], files[index - 1]);

				string str1 = files[0];
				str1 += files[index - 1];
				// 判断方案一是否可以
				bool isOK = IsSatisfy(str1, index);
				if (isOK)
				{
					cout << str1 << endl;
					return;
				}
				else
				{
					string str2 = files[index - 1];
					str2 += files[0];
					if (IsSatisfy(str2, index))
					{
						cout << str2 << endl;
						return;
					}
				}
				swap(files[0], files[i]);
				swap(files[j], files[index - 1]);
			}
		}
	}	
}
	
bool StrLenCompareFunc(const string &str1, const string str2)
{
	return (str1.length() < str2.length());
}

bool IsSatisfy(string str, int index)
{
	// 从1到index-1
	// files索引
	int start = 1;
	int end = index - 1;
	// 数组索引
	int shortIndex = 0;
	int longIndex = 0;
	while (start < end)
	{
		// 当前处理的文件的最小长度
		int curShrotLength = files[start].length();
		arr1[shortIndex++] = start++;

		// 如果长度相等
		while (files[start].length() == curShrotLength)
		{
			arr1[shortIndex++] = start++;
		}	
		if (start < end)
		{ // 只有还剩下较长的时候，才处理：有可能只有short的，而且short的都已被处理完了
			// 当前处理的文件的最大长度
			int curLongLength = files[end - 1].length();
			arr2[longIndex++] = --end;
			while (files[end - 1].length() == curLongLength)
			{
				arr2[longIndex++] = --end;
			}			
		}
		// 如果不是在中间，两者长度应该相等
		if (longIndex != 0)
		{ // 放到一个数组中
			for (int i = 0; i < longIndex; ++i)
			{
				arr1[shortIndex + i] = arr2[i];
			}
			shortIndex += longIndex;
		}
		// 如果不匹配，直接返回
		if (!IsMatch(str, arr1, shortIndex))
		{
			return false;
		}
		shortIndex = 0;
		longIndex = 0;
	}
	return true;
}

bool IsMatch(string str, int arr[], int size)
{	
	memset(IsUsed, 0, sizeof(IsUsed));
	for (int i = 0; i < size && !IsUsed[i]; ++i)
	{
		// 前半部分
		int len1 = files[arr[i]].length();
		if (strcmp(files[arr[i]].c_str(), (str.substr(0, len1)).c_str()) == 0)
		{
			// 说明是前半部分，开始找后半部分
			for (int j = size - 1; j >= 0 && !IsUsed[j] && (j != i); --j)
			{
				int len2 = files[arr[j]].length();
				if (strcmp(files[arr[j]].c_str(), (str.substr(len1)).c_str()) == 0)
				{					
					IsUsed[i] = true;
					IsUsed[j] = true;
					break;
				}
			}			
		}
		if (!IsUsed[i])
		{ // 如果前半部分没有匹配，找后半部分：如果前半部分没有匹配，则后半部分一定匹配
			// 说明是后半部分，开始找前半部分
			int totalLen = str.length();

			if (strcmp(files[arr[i]].c_str(), (str.substr(totalLen - len1)).c_str()) == 0)
			{
				for (int j = size - 1; j >= 0 && !IsUsed[j] && (j != i); --j)
				{
					int len2 = files[arr[j]].length();
					if (strcmp(files[arr[j]].c_str(), (str.substr(0, len2)).c_str()) == 0)
					{
						IsUsed[i] = true;
						IsUsed[j] = true;
						break;
					}
				}
			}			
		}
		if (!IsUsed[i])
		{ // 如果还没有找到
			return false;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		if (!IsUsed[i])
		{
			return false;
		}
	}
	return true;
}