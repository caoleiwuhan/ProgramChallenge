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


// �����ļ�
string files[300];
// �����ļ�����

// �����ļ�����
int arr1[300];
int arr2[300];

// bool����ʾ�Ƿ��ù�
bool IsUsed[300];

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
void Handle(int index);

/*
	������
*/
bool StrLenCompareFunc(const string &str1, const string str2);

/*
	�����ļ�str�����Ƿ�����
*/
bool IsSatisfy(string str, int index);

/*
	����str��arr��arrSize���Ƿ�ƥ��
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
	int count = 0;
	cin >> count;
	// ��β
	// ����
	cin.get();
	cin.get();
	while (count--)
	{
		string str;
		int index = 0;
		// getline��\n\r���Ե���
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
	// 1.�����ļ�������С��������
	sort(files, files + index, StrLenCompareFunc);
	// ����1��
	// ��һ���ǵ�һ�������һ��ƥ�䣡����
	int shortLen = files[0].length();
	int start = 1;
	while (start < index && files[start].length() == shortLen)
	{
		++start;
	}
	
	// �������еĶ����
	if (start != index)
	{
		for (int i = 0; i <= start; ++i)
		{			
			// ��i��j����
			swap(files[0], files[i]);

			string str1 = files[0];
			str1 += files[index - 1];
			// �жϷ���һ�Ƿ����
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
				// ��i��j����
				swap(files[0], files[i]);
				swap(files[j], files[index - 1]);

				string str1 = files[0];
				str1 += files[index - 1];
				// �жϷ���һ�Ƿ����
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
	// ��1��index-1
	// files����
	int start = 1;
	int end = index - 1;
	// ��������
	int shortIndex = 0;
	int longIndex = 0;
	while (start < end)
	{
		// ��ǰ������ļ�����С����
		int curShrotLength = files[start].length();
		arr1[shortIndex++] = start++;

		// ����������
		while (files[start].length() == curShrotLength)
		{
			arr1[shortIndex++] = start++;
		}	
		if (start < end)
		{ // ֻ�л�ʣ�½ϳ���ʱ�򣬲Ŵ����п���ֻ��short�ģ�����short�Ķ��ѱ���������
			// ��ǰ������ļ�����󳤶�
			int curLongLength = files[end - 1].length();
			arr2[longIndex++] = --end;
			while (files[end - 1].length() == curLongLength)
			{
				arr2[longIndex++] = --end;
			}			
		}
		// ����������м䣬���߳���Ӧ�����
		if (longIndex != 0)
		{ // �ŵ�һ��������
			for (int i = 0; i < longIndex; ++i)
			{
				arr1[shortIndex + i] = arr2[i];
			}
			shortIndex += longIndex;
		}
		// �����ƥ�䣬ֱ�ӷ���
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
		// ǰ�벿��
		int len1 = files[arr[i]].length();
		if (strcmp(files[arr[i]].c_str(), (str.substr(0, len1)).c_str()) == 0)
		{
			// ˵����ǰ�벿�֣���ʼ�Һ�벿��
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
		{ // ���ǰ�벿��û��ƥ�䣬�Һ�벿�֣����ǰ�벿��û��ƥ�䣬���벿��һ��ƥ��
			// ˵���Ǻ�벿�֣���ʼ��ǰ�벿��
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
		{ // �����û���ҵ�
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