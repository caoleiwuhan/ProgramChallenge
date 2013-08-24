#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstring>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_


// �ܴ���������
const int MAX_NUM = 3010;

// �ݴ�����
int arr[MAX_NUM];

// ��ǰ�������ݴ�С
int numCount;

// ��������
int map[MAX_NUM];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	�������飬�ж��ǲ���Jolly Jumper
*/
bool IsJollyJumper();

/*
	�ж�set�е����Ƿ��1��Num
*/
bool IsFromOneToNum();

int main()
{

//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/110201.inp";
//
//	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
//	ifstream fin;
//	fin.open(inputStr);	
//
//	cin.rdbuf(fin.rdbuf());	
//
//	ofstream fout;
//	fout.open(outputStr);
//
//	cout.rdbuf(fout.rdbuf());
//
//#endif

//	cout << "Test" << endl;
	MainStructure();
	return 0;
}

void MainStructure()
{
	// 1.��ȡ�������ݣ��ŵ�vector��
	char ch;
	while (cin.peek() != EOF)
	{
		// ���������ݸ���
		cin >> numCount;
		
		// �ݴ���
		int num;
		for (int i = 0; i < numCount; ++i)
		{
			cin >> num;
			arr[i] = num;
		}
		// ������������
		bool ans = IsJollyJumper();
		if (ans)
		{
			cout << "Jolly" << endl;
		}
		else
		{
			cout << "Not jolly" << endl;
		}

		// ��ȥ��β��'\n'
		cin.get();
	}
}

bool IsJollyJumper()
{ // ����֮��ľ���ֵ...
	// ����ֵ�����
	int count = numCount - 1;
	if (count <= 0)
	{
		return true;
	}

	// ��ʼ��map
	memset(map, 0, sizeof(map));
	
	for (int i = 0; i < count; ++i)
	{
		int num = abs(arr[i] - arr[i + 1]);
		// ��1��ʼ
		map[num]++;
	}
	// �ж��Ƿ��1��count
	return IsFromOneToNum();
}

bool IsFromOneToNum()
{	
	for (int i = 1; i < numCount; ++i)
	{
		// ����Ҳ���i
		if (map[i] != 1)
		{
			return false;
		}
	}
	return true;
}