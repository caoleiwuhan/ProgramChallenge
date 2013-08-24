#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//#define _MY_DEBUG_

// ���չ���
const int MAX_PARTY = 110;
// �������
const int MAX_DAY = 4000;

/*
	
*/
void MainStructure();

/*
	�������
*/
void HandleProcess();

/*
	��������
*/
void Input(int &daysNum, int &partyNum, int hartales[]);

/*
	����չ�����
*/
int HartalesDay(int days[], int daysNum, int hartales[], int partyNum);


int main()
{
	//cout << "Test" << endl;	

	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "D:/2��ս���/input/110203.inp";

	string outputStr = "D:/2��ս���/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

//	cout.rdbuf(fout.rdbuf());

#endif

	// Ҫ���������
	int count = 0;
	cin >> count;
	while (count--)
	{
		HandleProcess();
	}
}

void HandleProcess()
{
	// 1.��������
	// ������
	int daysNum = 0;
	// ������
	int partyNum = 0;
	// �����İչ�ָ��
	int hartales[MAX_PARTY];
	// ����
	int days[MAX_DAY];
	Input(daysNum, partyNum, hartales);

	// ����չ�����
	cout << HartalesDay(days, daysNum, hartales, partyNum) << endl;
}

int HartalesDay(int days[], int daysNum, int hartales[], int partyNum)
{
	memset(days, 0, sizeof(int) * MAX_DAY);
	//cout << sizeof(days) << endl;

	// ����ÿ������
	for (int i = 0; i < partyNum; ++i)
	{
		// �չ�ָ��
		int num = hartales[i];
		// ����ÿһ�죬��1��ʼ
		for (int j = 1; j <= daysNum; ++j)
		{
			// 1.�Ƿ���num�ı�����
			if (j % num == 0)
			{
				// 2.�����塢����
				// ��������Ϊ6����������Ϊ0
				if ((j % 7 == 6) || (j % 7 == 0))
				{
					continue;
				}
				// �������塢����,���չ�����һ
				++days[j];
			}
		}
	}
	// �չ�����
	int total = 0;
	for (int j = 1; j <= daysNum; ++j)
	{
		if (days[j] > 0)
		{
			++total;
		}
	}
	return total;
}

void Input(int &daysNum, int &partyNum, int hartales[])
{
	cin >> daysNum;
	cin >> partyNum;
	for (int i = 0; i < partyNum; ++i)
	{
		cin >> hartales[i];
	}
}