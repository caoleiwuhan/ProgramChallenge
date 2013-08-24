#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>


using namespace std;

#define _MY_DEBUG_

// 字典
string strmap[30000];
int index = 0;


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
void Handle(string statrStr, string endStr);



/*
	排序函数
*/
bool StrLenCompare(const string &lhs, const string &rhs);

/*
	判断str1和str2是否只相差一个字母
*/
bool IsDifferenceByOneChar(string str1, string str2);

/*
	从strmap中的start到end找到str，如果没有，返回-1
	包括start和end
*/
int FindStrInMap(int start, int end, string str);


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
	// 读入字典
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		strmap[index++] = str;
	}
	// 首先对strmap按照str长度从小到大排序
	sort(strmap, strmap + index, StrLenCompare);
	int ***ans = new int **[17];
	int ***map = new int **[17];
	// 初始化
	for (int i = 0; i < 17; ++i)
	{
		ans[i] = 0;
		map[i] = 0;
	}

	// 记录单词长度为i的开始和结束位置
	int starts[17];
	int ends[17];
	// 预处理字典
	for (int i = 0; i < index; )
	{
		int start = i;
		int end = i;
		int curStrLen = strmap[i].length();
		int curLen = 0;
		while (strmap[++i].length() == curStrLen)
		{
			end = i;
			++curLen;
		}
		// 当前长度为curStrLen的单词个数共有curLen个
		// 初始化ans、man、lens ：构造
		starts[curStrLen] = start;
		ends[curStrLen] = end;
		// 初始化指针，使得ans[curStrLen] = int[len][len]
		ans[curStrLen] = new int *[curLen];
		map[curStrLen] = new int *[curLen];
		for (int m = 0; m < curLen; ++m)
		{
			ans[curStrLen][m] = new int[curLen];
			map[curStrLen][m] = new int[curLen];
		}
		// 初始化
		for (int m = start; m <= end; ++m)
		{
			for (int n = start; n <= end; ++n)
			{
				ans[curStrLen][m][n] = 0;				
			}
		}
		// 初始化长度为1的!
		for (int m = start; m <= end; ++m)
		{
			for (int n = start; n <= end; ++n)
			{
				if (IsDifferenceByOneChar(strmap[m], strmap[n]))
				{
					ans[curStrLen][m][n] = 1;
					//map[curStrLen][m][n] = 1;
				}
			}
		}

		// 第m个字母，到第n个字母，经过第k个字母
		for (int m = start; m <= end; ++m)
		{
			for (int n = start; n <= end; ++n)
			{
				int min = 0x7fffffff;
				for (int k = start; k <= end; ++k)
				{
					if (ans[curStrLen][m][k] && ans[curStrLen][k][n])
					{
						// 如果从m到k，以及从k到n有路
						int cur = ans[curStrLen][m][k] + ans[curStrLen][k][n];
						if (cur < min)
						{
							min = cur;
							ans[curStrLen][m][n] = cur;
							map[curStrLen][m][n] = k;
						}
					}
				}
			}
		}
	}

	int count = 0;
	// 读入单词并进行处理
	while (getline(cin, str))
	{
		stringstream ss(str);
		string startStr;
		string endStr;
		ss << startStr;
		ss << endStr;
		int len = startStr.length();
		// 输出每一组数据之间的空行
		if (count != 0)
		{
			cout << endl;
		}
		++count;
		// 长度相等
		if (len != endStr.length())
		{
			cout << "No solution." << endl;
			continue;
		}
		else
		{
			// 从strmap中找到两个str的位置
			int start = starts[len];
			int end = ends[len];
			int startIndex = FindStrInMap(start, end, startStr);
			int endIndex = FindStrInMap(start, end, endStr);
			if (startIndex == -1 || endIndex == -1)
			{
				cout << "No solution." << endl;
				continue;
			}
			if (ans[len][startIndex][endIndex] == 0)
			{
				cout << "No solution." << endl;
				continue;			
			}
			else
			{ // 结果
				vector<string> result;
				result[0] = startStr;
				int startVecIndex = 0;
				result[ans[len][startIndex][endIndex] + 1] = endStr;

				// 用栈模拟递归调用
				stack<int> s;
				// 每次入栈3个值
				s.push(endIndex);
				s.push(startVecIndex);
				s.push(startIndex);
				while (!s.empty())
				{
					int tmpStart = s.top();
					s.pop();
					int curStartVecIndex = s.top();
					s.pop();
					int tmpEnd = s.top();
					s.pop();
					int k = map[len][tmpStart][tmpEnd];
					if (k != 0)
					{
						int curMiddleVecIndex = curStartVecIndex + ans[len][tmpStart][tmpEnd];
						result[curMiddleVecIndex] = strmap[k];
						s.push(k);
						s.push(curStartVecIndex);
						s.push(tmpStart);

						s.push(tmpEnd);
						s.push(curMiddleVecIndex);
						s.push(k);
					}
					// 如果k为0，不管					
				}
				for (int i = 0; i < result.size(); ++i)
				{
					cout << result[i] << endl;
				}
			}
		}
	}
	// 释放内存
	for (int i = 0; i < 17; ++i)
	{
		// 如果被分配过内存
		if (ans[i])
		{
			int len = ends[i] - starts[i] + 1;
			for (int j = 0; j < len; ++j)
			{
				delete ans[i][j];
				delete map[i][j];
			}
			delete ans[i];
		}
	}
}


bool StrLenCompare(const string &lhs, const string &rhs)
{
	return (lhs.length() < rhs.length());
}

bool IsDifferenceByOneChar(string str1, string str2)
{
	int len = str1.length();
	int totalDif = 0;
	for (int i = 0; i < len; ++i)
	{
		if (str1[i] != str2[i])
		{
			++totalDif;
			if (totalDif > 1)
			{
				return false;
			}
		}
	}
	if (totalDif == 1)
	{
		return true;
	}
	return false;
}

int FindStrInMap(int start, int end, string str)
{
	for (int i = start; i <= end; ++i)
	{
		if (strmap[i] == str)
		{
			return i;
		}
	}
	return -1;
}