#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_

// һ���Ƶ���Ŀ
const int NUM_CARD = 52;

// ϴ�Ƶ������Ŀ
const int NUM_STACK = 110;

// ϴ�Ƶķ��� : ��1��52
int stackMethod[NUM_STACK][NUM_CARD + 1];

int totalNum[10000];


// ��ɫ����Ϊ4
const int NUM_KIND = 4;
// һ�ֻ�ɫ���Ƹ���Ϊ13
const int NUM_ONE_KIND_CARD = 13;

// ��ɫ��
string cardKind[NUM_KIND] = 
{
	"Clubs",
	"Diamonds",
	"Hearts",
	"Spades"
};

/*
	MainStructure: ���ṹ
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
	��ȡ��������
*/
void Input(int &numOfStack, vector<int> intVec, int &numOfSwap);

/*
	ϴ�ƣ��õ�index�ַ���������from��to
*/
void Suffle(int index, int from[], int to[]);

/*
	������
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/4.outp";
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
	// 1. ������������
	int count = 0;
	cin >> count;
	
	while (count--)
	{
		// 2.��ÿһ�����ݽ��д���
		Handle();
		if (count)
		{
			cout << endl;
		}
	}
}

void Handle()
{
	// 1.����ϴ�Ƶķ�����
	int numOfStack = 0;
	vector<int> intVec;
	int numOfSwap = 0;
	Input(numOfStack, intVec, numOfSwap);
	
	// 2.���������ݴ�����
	int ans[2][NUM_CARD + 1];
	for (int i = 1; i <= NUM_CARD; ++i)
	{
		ans[0][i] = i;
	}
	// 3.����
	int index = 0;
	//int total = intVec.size();
	int total = numOfSwap;
	while (index < total)
	{
		// �����index�����ݣ����indexΪż�������ans[0]->ans[1]�������ans[1]->ans[0]
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
	// 4.���:���indexΪ������˵�������ans[1]�У�������ans[0]��
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

// ��i�ַ�������0��ʼ
// ÿһ���ƣ���1��ʼ
void Input(int &numOfStack, vector<int> intVec, int &numOfSwap)
{
	cin >> numOfStack;
	for (int i = 0; i < numOfStack; ++i)
	{
		// ��ȡ��i��ϴ�Ʒ���
		for (int j = 1; j <= NUM_CARD; ++j)
		{
			cin >> stackMethod[i][j];
		}
	}
	// ��ȡ����������������У������
	// �ݴ�string
	string str;
	// �ݴ�num
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
		// num��j��
		i = stackMethod[index][j];
		// ��ʾϴ��ǰ�ĵ�i������ϴ�ƺ�ĵ�j��
		to[j] = from[i];
	}
}

void OutPut(int res[])
{
	for (int j = 1; j <= NUM_CARD; ++j)
	{
		// 1.��ɫ�� 
		int kind = (res[j] - 1) / NUM_ONE_KIND_CARD;

		// 2.��С
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