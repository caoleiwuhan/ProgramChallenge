#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

//#define _MY_DEBUG_



// ���������50
char matrix[60][60];

// 8�������x��y����
int map[8][2] = 
{
	0, 1,	// ����
	1, 1,	// ����
	1, 0,	// ����
	1, -1,	// ����
	0, -1,	// ����
	-1, -1,	// ����
	-1, 0,	// ����
	-1, 1	// ����
};



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
void Handle();

/*
	����ÿ�������ھ����е�λ��
*/
void CalclulateWordPos(string word, int m, int n, int &posX, int &posY);

/*
	����8������
*/
bool IterateEightDirection(int startX, int startY, int m, int n, int direction, string word);


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
	//cout << "Test" << endl;
	// ��������
	int count = 0;
	cin >> count;
	while (count--)
	{		
		// ����ÿһ������
		Handle();

		if (count)
		{
			cout << endl;
		}
	}
}

void Handle()
{	
	// ������M
	int m;
	int n;
	// ��ȡ����
	cin >> m >> n;
	// ��β������
	cin.get();
	// ��ʼ������
	for (int i = 0; i < m; ++i)
	{
		string str;
		char ch;
		getline(cin, str);
		stringstream ss(str);
		for (int j = 0; j < n; ++j)
		{
			ss >> ch;
			if (isupper(ch))
			{
				ch = tolower(ch);
			}
			matrix[i][j] = ch;
		}
	}
	// ��ȡ���ʸ���
	int wordCount = 0;
	cin >> wordCount;
	// ��β������
	cin.get();
	string word;
	while (wordCount--)
	{
		cin >> word;
		int posX, posY;
		for (int i = 0; i < word.size(); ++i)
		{
			word[i] = tolower(word[i]);
		}
		CalclulateWordPos(word, m, n, posX, posY);
		cout << posX + 1 << " " << posY + 1<< endl;
	}
}

void CalclulateWordPos(string word, int m, int n, int &posX, int &posY)
{
	int len = word.size() - 1;
	// �ӵ�һ��λ�ÿ�ʼ��8���������
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				// �ڿ�ʼ֮ǰ���жϳ����Ƿ������㣺				
				int endX = i + map[k][0] * len;
				int endY = j + map[k][1] * len;
				if (endX < 0 || endX >= m ||
					endY < 0 || endY >= n)
				{
					continue;
				}

				if (IterateEightDirection(i, j, m, n, k, word))
				{
					posX = i;
					posY = j;
					return;
				}
			}
		}
	}

}

bool IterateEightDirection(int startX, int startY, int m, int n, int direction, string word)
{
	int len = word.size();
	int index = 0;
	for (int i = startX, j = startY; 
			(i >= 0 && i < m) && (j >= 0 && j < n) &&(index < len); 
				i += map[direction][0], j += map[direction][1], ++index)
	{
		if (matrix[i][j] != word[index])
		{
			return false;
		}
	}
	if (index == len)
	{
		return true;
	}
	return false;
}