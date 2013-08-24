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



// 行列最大是50
char matrix[60][60];

// 8个方向的x、y步进
int map[8][2] = 
{
	0, 1,	// 向右
	1, 1,	// 右下
	1, 0,	// 向下
	1, -1,	// 左下
	0, -1,	// 向左
	-1, -1,	// 左上
	-1, 0,	// 向上
	-1, 1	// 右上
};



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
void Handle();

/*
	计算每个单词在矩阵中的位置
*/
void CalclulateWordPos(string word, int m, int n, int &posX, int &posY);

/*
	遍历8个方向
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
	//cout << "Test" << endl;
	// 测试组数
	int count = 0;
	cin >> count;
	while (count--)
	{		
		// 处理每一组数据
		Handle();

		if (count)
		{
			cout << endl;
		}
	}
}

void Handle()
{	
	// 行数：M
	int m;
	int n;
	// 读取行列
	cin >> m >> n;
	// 行尾结束符
	cin.get();
	// 初始化矩阵
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
	// 读取单词个数
	int wordCount = 0;
	cin >> wordCount;
	// 行尾结束符
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
	// 从第一个位置开始向8个方向遍历
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < 8; ++k)
			{
				// 在开始之前先判断长度是否能满足：				
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