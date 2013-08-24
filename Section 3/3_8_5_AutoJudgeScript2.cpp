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
	���100�У�ÿ�����120���ַ�
*/
string answerStr;
string outputStr;


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	Handle������ÿһ���е�ÿһ��ʵ��
*/
int Handle();

/*
	�Ƚ������ַ�����
	���أ�
		1�����
		2��������ȣ�
		3��error
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
	// ����int:��׼����
	int answerCount = 0;
	// �������
	int outputCount = 0;
	// �������ݵ�ǰ����
	int runCount = 1;
	// ansCountΪ0ʱ����
	while (cin >> answerCount && answerCount != 0)
	{
		answerStr = "";
		outputStr = "";
		// �����׼�𰸣���ansCount��
		// ȥ����β\n
		cin.get();
		string str;
		int index = 0;
		for (index = 0; index < answerCount; ++index)
		{
			getline(cin, str);
			answerStr += str;
			answerStr.append(1, '\n');
		}
		// ��ȡ����𰸣���outputCount��
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
	// str2���ܱ�str1��...
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
		{ // ��ȫ��ͬ
			++index1;
			++index2;
			continue;
		}
		// ����ͬ
		int isCh1Digit = isdigit(ch1);
		int isCh2Digit = isdigit(ch2);
		if (isCh1Digit && !isCh2Digit)
		{ // ch1Ϊ���֣�ch2���ǣ�presentation error
			++index2;
			ans = 2;
		}
		else if (!isCh1Digit && isCh2Digit)
		{ // ch1�������֣�ch2��
			++index1;
			ans = 2;
		}
		else if (isCh1Digit && isCh2Digit)
		{ // �������֣����Ҳ���ȣ�ֱ�ӷ��ش���
			ans = 3;
			return ans;
		}
		else 
		{ // ���߲���ȣ����Ҷ���������
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
	{ // str1������ĸ
		ans = 2;
		// ���str1�а��������֣���error
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
	{ // str2������ĸ
		ans = 2;
		// ���str1�а��������֣���error
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