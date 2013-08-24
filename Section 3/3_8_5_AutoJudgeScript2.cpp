#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

//#define _MY_DEBUG_

/*
	最多100行，每行最多120个字符
*/
string answerStr;
string outputStr;


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
int Handle();

/*
	比较两个字符串：
	返回：
		1：相等
		2：数字相等，
		3：error
*/
int CompareTwoStr(string str1, string str2);

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
	// 读入int:标准答案数
	int answerCount = 0;
	// 输出答案数
	int outputCount = 0;
	// 测试数据当前组数
	int runCount = 1;
	// ansCount为0时结束
	while (cin >> answerCount && answerCount != 0)
	{
		answerStr = "";
		outputStr = "";
		// 读入标准答案，共ansCount行
		// 去掉行尾\n
		cin.get();
		string str;
		int index = 0;
		for (index = 0; index < answerCount; ++index)
		{
			getline(cin, str);
			answerStr += str;
			answerStr.append(1, '\n');
		}
		// 读取输出答案，共outputCount行
		cin >> outputCount;
		cin.get();
		for (index = 0; index < outputCount; ++index)
		{
			getline(cin, str);
			outputStr += str;
			outputStr.append(1, '\n');
		}

		//cout << answerStr;
		//cout << outputStr;

		int ans = Handle();	
		cout << "Run #" << (runCount++) << ": ";
		if (ans == 1)
		{
			cout << "Accepted" << endl;
		}
		if (ans == 2)
		{
			cout << "Presentation Error" << endl;
		}
		if (ans == 3)
		{
			cout << "Wrong Answer" << endl;
		}
	}
}

int Handle()
{	
	return CompareTwoStr(answerStr, outputStr);		
}
	

int CompareTwoStr(string str1, string str2)
{
	int ans = 1;
	// str2可能比str1长...
	int len1 = str1.length();
	int len2 = str2.length();
	int index1 = 0;
	int index2 = 0;
	while (index1 < len1 && index2 < len2)
	{
		char ch1 = str1[index1];
		char ch2 = str2[index2];
		// 
		if (ch1 == ch2)
		{ // 完全相同
			++index1;
			++index2;
			continue;
		}
		// 不相同
		int isCh1Digit = isdigit(ch1);
		int isCh2Digit = isdigit(ch2);
		if (isCh1Digit && !isCh2Digit)
		{ // ch1为数字，ch2不是：presentation error
			++index2;
			ans = 2;
		}
		else if (!isCh1Digit && isCh2Digit)
		{ // ch1不是数字，ch2是
			++index1;
			ans = 2;
		}
		else if (isCh1Digit && isCh2Digit)
		{ // 都是数字，并且不相等，直接返回错误
			ans = 3;
			return ans;
		}
		else 
		{ // 两者不相等，并且都不是数字
			ans = 2;
			++index1;
			++index2;
		}
	}
	if (index1 == len1 && index2 == len2)
	{
		return ans;
	}
	else if (index1 < len1)
	{ // str1还有字母
		ans = 2;
		// 如果str1中包含有数字，则error
		while (index1 < len1)
		{
			if (isdigit(str1[index1++]))
			{
				ans = 3;
				return ans;
			}			
		}
	}
	else
	{ // str2还有字母
		ans = 2;
		// 如果str1中包含有数字，则error
		while (index2 < len2)
		{
			if (isdigit(str2[index2++]))
			{
				ans = 3;
				return ans;
			}			
		}
	}
	return ans;
}