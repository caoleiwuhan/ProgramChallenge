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

// �ݴ����ַ�
char ans[1010];

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
void Handle(string str1, string str2);

/*
	��ȡ��������
*/
void Input();



/*
	������
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
	// ÿ������Ϊһ�����룬���ֻ��һ�е��򲻴���
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
			// ���㲢��ӡ
			Handle(str1, str2);
		}
	}
}

void Handle(string str1, string str2)
{	
	memset(ans, 0, sizeof(ans));
	int index = 0;
	// 1.����str1��str2�Ĺ�����ĸ
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
	// ��ans��������
	sort(ans, ans + index);
	for (int i = 0; i < index; ++i)
	{
		cout << ans[i];
	}
	cout << endl;
}
