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
	���⣺��Ŀ����ȷ��ֻ����ĸ�ı��룡����
	û�п��ǵ���ĸ�Կո�����������
*/

// ��ʼ�ַ���
string initStr = "the quick brown fox jumps over the lazy dog";
//				  xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj

// ��ĸӳ�����a��z
char charMap[30];

// �������е�����str
string crypts[110];

/*
	������ͬ��ĸ�����ڲ�ͬλ�õ������������ͬ����λ�ó��֣�
*/

/*
	�ж��Ƿ����ӳ��
		��֤������ͬ��map[i] = ch ��ʾ��i(����ĸ��)����ĸ��ʾλch
*/
bool IsMapOK(string str);


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
void Handle(string crypts[], int len);

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
	// ȥ��\n
	cin.get();
	int initStrLen = initStr.size();
	// ȥ������
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

// Ĭ����Сд
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
				// �Ѿ�ӳ���
				if (charMap[index] != initStr[i])
				{
					return false;
				}
			}
			else
			{
				// �ַ���Ӧ�ı������ַ����ո��Ӧ�ı����ǿո�
				if (!isalpha(initStr[i]))
				{
					return false;
				}
				charMap[index] = initStr[i];
			}
		}
		else
		{ // ���붼�����ַ�
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