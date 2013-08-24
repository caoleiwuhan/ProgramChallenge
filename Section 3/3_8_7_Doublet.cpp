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

// �ֵ�
string strmap[30000];
int index = 0;


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
void Handle(string statrStr, string endStr);



/*
	������
*/
bool StrLenCompare(const string &lhs, const string &rhs);

/*
	�ж�str1��str2�Ƿ�ֻ���һ����ĸ
*/
bool IsDifferenceByOneChar(string str1, string str2);

/*
	��strmap�е�start��end�ҵ�str�����û�У�����-1
	����start��end
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
	// �����ֵ�
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		strmap[index++] = str;
	}
	// ���ȶ�strmap����str���ȴ�С��������
	sort(strmap, strmap + index, StrLenCompare);
	int ***ans = new int **[17];
	int ***map = new int **[17];
	// ��ʼ��
	for (int i = 0; i < 17; ++i)
	{
		ans[i] = 0;
		map[i] = 0;
	}

	// ��¼���ʳ���Ϊi�Ŀ�ʼ�ͽ���λ��
	int starts[17];
	int ends[17];
	// Ԥ�����ֵ�
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
		// ��ǰ����ΪcurStrLen�ĵ��ʸ�������curLen��
		// ��ʼ��ans��man��lens ������
		starts[curStrLen] = start;
		ends[curStrLen] = end;
		// ��ʼ��ָ�룬ʹ��ans[curStrLen] = int[len][len]
		ans[curStrLen] = new int *[curLen];
		map[curStrLen] = new int *[curLen];
		for (int m = 0; m < curLen; ++m)
		{
			ans[curStrLen][m] = new int[curLen];
			map[curStrLen][m] = new int[curLen];
		}
		// ��ʼ��
		for (int m = start; m <= end; ++m)
		{
			for (int n = start; n <= end; ++n)
			{
				ans[curStrLen][m][n] = 0;				
			}
		}
		// ��ʼ������Ϊ1��!
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

		// ��m����ĸ������n����ĸ��������k����ĸ
		for (int m = start; m <= end; ++m)
		{
			for (int n = start; n <= end; ++n)
			{
				int min = 0x7fffffff;
				for (int k = start; k <= end; ++k)
				{
					if (ans[curStrLen][m][k] && ans[curStrLen][k][n])
					{
						// �����m��k���Լ���k��n��·
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
	// ���뵥�ʲ����д���
	while (getline(cin, str))
	{
		stringstream ss(str);
		string startStr;
		string endStr;
		ss << startStr;
		ss << endStr;
		int len = startStr.length();
		// ���ÿһ������֮��Ŀ���
		if (count != 0)
		{
			cout << endl;
		}
		++count;
		// �������
		if (len != endStr.length())
		{
			cout << "No solution." << endl;
			continue;
		}
		else
		{
			// ��strmap���ҵ�����str��λ��
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
			{ // ���
				vector<string> result;
				result[0] = startStr;
				int startVecIndex = 0;
				result[ans[len][startIndex][endIndex] + 1] = endStr;

				// ��ջģ��ݹ����
				stack<int> s;
				// ÿ����ջ3��ֵ
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
					// ���kΪ0������					
				}
				for (int i = 0; i < result.size(); ++i)
				{
					cout << result[i] << endl;
				}
			}
		}
	}
	// �ͷ��ڴ�
	for (int i = 0; i < 17; ++i)
	{
		// �����������ڴ�
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