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

#define _MY_DEBUG_

// ����
int arr[16][16];


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	����n��k�����ؽ��������
*/
unsigned BackStace(int n, int k);

/*
	n������
	k������
	step����ǰ����
	ans������
	line����ǰ�����������ֻ�ܴ�����	
*/
void Solve(int n, int k, int step, unsigned &ans, int line);

/*
	�����line�е���ʼ�ͽ���λ��
*/
void CalPosition(int n, int line, int &start, int &end);

void Test();

int main()
{
	MainStructure();
	//Test();
	return 0;
}

void Test()
{
	int start, end;
	CalPosition(4, 1, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 2, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 3, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 4, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 5, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 6, start, end);
	cout << start << " " << end << endl;
	CalPosition(4, 7, start, end);
	cout << start << " " << end << endl;
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
	int n, k;
	while (cin >> n >> k)
	{
		if (n == 0 && k == 0)
		{
			break;
		}
		unsigned ans = 0;
		ans = BackStace(n, k);
		cout << ans << endl;
	}
}



unsigned BackStace(int n, int k)
{
	unsigned ans = 0;
	memset(arr, 0, sizeof(arr));
	if (k > 2 * n)
	{
		return 0;
	}
	// �ӵ�һ�п�ʼ�ɣ�
	Solve(n, k, 0, ans, 1);

	return ans;
}

void Solve(int n, int s, int step, unsigned &ans, int line)
{	
	if (step == s)
	{
		++ans;
		return;
	}
	else
	{
		// ������а�����
		for (int i = line; i < 2 * n; ++i)
		{ 
			// ���ڵ�ǰ��i�У�������ʵλ�úͽ���λ��
			int start = 0;
			int end = 0;
			CalPosition(n, i, start, end);
			// ���ڸ��е�ÿһ�񣬰�����
			for (int j = start; j <= end; j += 2)
			{
				bool isOK = true;
				// ��ǰ����еĵ�ǰ���Ƿ��Ѿ������
				for (int k = 1; k < line; ++k)
				{
					if (arr[k][j] == 1)
					{
						isOK = false;
						break;
					}
				}
				if (isOK)
				{
					// ������ԣ���䵱ǰ����
					arr[i][j] = 1;
					// ���»���
					Solve(n, s, step + 1, ans, i + 1);
					// ���У��ָ�
					arr[i][j] = 0;
				}
			}
		}
	}
}


void CalPosition(int n, int line, int &start, int &end)
{
	// �м��е�����
	int middle = n;	
	if (line <= n)
	{
		int index = 1;
		start = 8;
		end = 8;
		while (index < line)
		{
			--start;
			++end;
			++index;
		}
	}
	else
	{
		int index = 2 * n - 1;
		start = 8;
		end = 8;
		while (index > line)
		{
			--start;
			++end;
			--index;
		}
	}
}