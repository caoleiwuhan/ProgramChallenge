#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_

// 一副牌的数目
const int NUM_CARD = 52;

// 洗牌的最大数目
const int NUM_STACK = 110;

// 洗牌的方法 : 从1到52
int stackMethod[NUM_STACK][NUM_CARD + 1];

int totalNum[10000];


// 花色个数为4
const int NUM_KIND = 4;
// 一种花色的牌个数为13
const int NUM_ONE_KIND_CARD = 13;

// 花色：
string cardKind[NUM_KIND] = 
{
	"Clubs",
	"Diamonds",
	"Hearts",
	"Spades"
};

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	Handle
*/
void Handle();

/*
	读取输入数据
*/
void Input(int &numOfStack, vector<int> intVec, int &numOfSwap);

/*
	洗牌，用地index种方法，并从from到to
*/
void Suffle(int index, int from[], int to[]);

/*
	输出结果
*/
void OutPut(int res[]);

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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/4.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	cout.rdbuf(fout.rdbuf());

	Process();
#endif
		
}

void Process()
{
	// 1. 读入数据组数
	int count = 0;
	cin >> count;
	
	while (count--)
	{
		// 2.对每一组数据进行处理
		Handle();
		if (count)
		{
			cout << endl;
		}
	}
}

void Handle()
{
	// 1.读入洗牌的方法数
	int numOfStack = 0;
	vector<int> intVec;
	int numOfSwap = 0;
	Input(numOfStack, intVec, numOfSwap);
	
	// 2.构造两个暂存数组
	int ans[2][NUM_CARD + 1];
	for (int i = 1; i <= NUM_CARD; ++i)
	{
		ans[0][i] = i;
	}
	// 3.处理
	int index = 0;
	//int total = intVec.size();
	int total = numOfSwap;
	while (index < total)
	{
		// 处理第index组数据，如果index为偶数，则从ans[0]->ans[1]，否则从ans[1]->ans[0]
		if (index & 1)
		{
			//Suffle(intVec[index] - 1, ans[1], ans[0]);
			Suffle(totalNum[index] - 1, ans[1], ans[0]);
		}
		else
		{
			//Suffle(intVec[index] - 1, ans[0], ans[1]);
			Suffle(totalNum[index] - 1, ans[0], ans[1]);
		}
		++index;
	}
	// 4.输出:如果index为奇数，说明结果在ans[1]中，否则在ans[0]中
	if (index & 1)
	{
		OutPut(ans[1]);
	}
	else
	{
		OutPut(ans[0]);
	}
	//cout << endl;
}

// 第i种方法，从0开始
// 每一张牌，从1开始
void Input(int &numOfStack, vector<int> intVec, int &numOfSwap)
{
	cin >> numOfStack;
	for (int i = 0; i < numOfStack; ++i)
	{
		// 读取第i种洗牌方法
		for (int j = 1; j <= NUM_CARD; ++j)
		{
			cin >> stackMethod[i][j];
		}
	}
	// 读取若干整数，如果空行，则结束
	// 暂存string
	string str;
	// 暂存num
	int num = 0;
	cin.get();
	int index = 0;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		num = atoi(str.c_str());
		//intVec[index++] = num;
		totalNum[index++] = num;
	}
	numOfSwap = index;
}

void Suffle(int index, int from[], int to[])
{
	memset(to, 0, sizeof(int) * (NUM_CARD + 1));
	int i = 0;
	for (int j = 1; j <= NUM_CARD; ++j)
	{
		// num在j处
		i = stackMethod[index][j];
		// 表示洗牌前的第i张牌在洗牌后的第j张
		to[j] = from[i];
	}
}

void OutPut(int res[])
{
	for (int j = 1; j <= NUM_CARD; ++j)
	{
		// 1.花色： 
		int kind = (res[j] - 1) / NUM_ONE_KIND_CARD;

		// 2.大小
		int num = ((res[j] - 1) % NUM_ONE_KIND_CARD);
		if (num >= 0 && num <= 8)
		{
			cout << (num + 2);
		}
		if (num == 9)
		{
			cout << "Jack";
		}
		if (num == 10)
		{
			cout << "Queen";
		}
		if (num == 11)
		{
			cout << "King";
		}
		if (num == 12)
		{
			cout << "Ace";
		}
		cout << " of " << cardKind[kind] << endl;
	}
}