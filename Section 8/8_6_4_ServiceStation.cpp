#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

//#define _MY_DEBUG_


// ���ݽṹ������:���Ϊ35
bool metrix[36][36];

bool res[36];

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	������Сstation�������û�У�����0
*/
int MinNumOfStation(int vNum);


/*
	���ص�����Ϊiʱ���Ƿ����
*/
bool IsOK(int i, int vNum);

/*
	���û��ݷ���1��vNum������i������������ж��Ƿ���������
	ֻ��ʹ��cur֮�����
*/
bool BackTrace(int *comNums, int vNum, int i, int cur, int step);

/*
	�Ƿ���������
*/
bool IsComNumOK(int *comNums, int i, int vNum);

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
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*
	ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());
	*/

#endif

	Process();
			
}
void Process()
{
	int vNum = 0;
	int lNum = 0;

	int v1, v2;

	while (cin >> vNum >> lNum)
	{
		if (vNum == 0 && lNum == 0)
		{
			break;
		}
		memset(metrix, false, sizeof(metrix));
		for (int i = 0; i < lNum; ++i)
		{
			cin >> v1 >> v2;
			metrix[v1][v2] = true;
			metrix[v2][v1] = true;	
		}
		cout << MinNumOfStation(vNum) << endl;
	}

}


int MinNumOfStation(int vNum)
{
	int ans = 0;
	for (int i = 1; i <= vNum; ++i)
	{
		if (IsOK(i, vNum))
		{
			ans = i;
			break;
		}
	}
	return ans;
}

bool IsOK(int i, int vNum)
{
	// �����
	int *comNums = new int[vNum];
	// �û��ݷ�����i�������
	bool ans = BackTrace(comNums, vNum, i, 1, 0);
	delete []comNums;
	return ans;
}

bool BackTrace(int *comNums, int vNum, int i, int cur, int step)
{
	if (step == i)
	{
		// �ж��Ƿ���������
		if (IsComNumOK(comNums, i, vNum))
		{
			return true;
		}
		return false;
	}
	for (int s = cur; s <= vNum; ++s)
	{
		comNums[step] = s;
		if (BackTrace(comNums, vNum, i, s + 1, step + 1))
		{
			return true;
		}
	}
	return false;
}

bool IsComNumOK(int *comNums, int i, int vNum)
{
	memset(res, false, sizeof(res));
	for (int s = 0; s < i; ++s)
	{
		int cur = comNums[s];
		res[cur] = true;
		for (int t = 1; t <= vNum; ++t)
		{
			if (metrix[cur][t])
			{
				res[t] = true;
			}
		}
	}
	for (int s = 1; s <= vNum; ++s)
	{
		if (!res[s])
		{
			return false;
		}
	}
	return true;
}