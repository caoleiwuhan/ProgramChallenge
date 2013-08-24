#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>


using namespace std;

//#define _MY_DEBUG_

// 暂存结果字符
char ans[1010];

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
void Handle(string str1, string str2);

/*
	读取输入数据
*/
void Input();



/*
	输出结果
*/
void OutPut();

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
	// 每两行作为一个输入，如果只有一行的则不处理
	string str1;
	string str2;
	string str;
	bool isSecond = false;
	while (getline(cin, str))
	{
		if (!isSecond)
		{
			str1 = str;
			isSecond = true;			
		}
		else
		{
			str2 = str;
			isSecond = false;
			// 计算并打印
			Handle(str1, str2);
		}
	}
}

void Handle(string str1, string str2)
{	
	memset(ans, 0, sizeof(ans));
	int index = 0;
	// 1.计算str1、str2的公共字母
	int len1 = str1.size();
	int len2 = str2.size();
	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			if (str1[i] == str2[j])
			{
				// 
				ans[index++] = str1[i];
				str2.erase(j, 1);
				--len2;
				break;
			}
		}
	}
	// 对ans进行排序
	sort(ans, ans + index);
	for (int i = 0; i < index; ++i)
	{
		cout << ans[i];
	}
	cout << endl;
}
