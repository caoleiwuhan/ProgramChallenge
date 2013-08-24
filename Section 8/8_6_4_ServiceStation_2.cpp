#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;

//#define _MY_DEBUG_

const long long ONE = 1;

// ��i��station�ܵ���ĵط�
long long station[36];
// ��i��֮�����еĶ����ܵ����
long long last[36];


//char buffer[65];


/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	����
	vNum:�ܵ���
	cur����ǰ����һ����ʼ
	state����ǰ״̬
	need����Ҫ�ĵ���
	step�����е���step������
*/
bool DFS(int vNum, int cur, long long state, int need, int step);

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
	//8 cout << sizeof(long long) << endl;
	int vNum, lNum;
	int v1, v2;
	while (cin >> vNum >> lNum)
	{
		if (vNum == 0 && lNum == 0)
		{
			break;
		}
		memset(station, 0, sizeof(station));


		//memset(last, 0, sizeof(station));
		// ���������Լ����Լ��ɴ��1���ͽ�����0λ
		for (int i = 0; i < vNum; ++i)
		{

//itoa(ONE << i, buffer, 2);
//cout << buffer << endl;

			station[i + 1] |= (ONE << i);
		}
		for (int i = 0; i < lNum; ++i)
		{
			cin >> v1 >> v2;
			// ����v1��v2֮��ɴ�
			station[v1] |= (ONE << (v2 - 1));
			station[v2] |= (ONE << (v1 - 1));			
		}

//for (int i = 1; i <= vNum; ++i)
//{
//	itoa(station[i], buffer, 2);
//	cout << buffer << endl;
//}


		last[vNum] = station[vNum];
		for (int i = vNum - 1; i > 0; --i)
		{
			last[i] = last[i + 1] | station[i];
		}

		if (lNum == 0)
		{
			cout << vNum << endl;
			continue;
		}

		// �����i��ʾ����
		for (int i = 1; i <= vNum; ++i)
		{
			long long state = 0;
			if (DFS(vNum, 1, state, i, 0))
			{
				cout << i << endl;
				break;
			}
		}
	}
}

bool DFS(int vNum, int cur, long long state, int need, int step)
{
	// ��������
	if (state == ((ONE << vNum) - 1))
	{
		return true;
	}

	// �������Ҳû�н��
	if (step == need)
	{
		return false;
	}
	
	for (int i = cur; i <= vNum; ++i)
	{
		// ����������еĶ���stationҲ����������������ֱ�Ӽ�֦����


//itoa(state, buffer, 2);
//cout << "state:" << buffer << endl;
//
//itoa((ONE << vNum) - 1, buffer, 2);
//cout << "answe:" << buffer << endl;
//
//itoa(last[i], buffer, 2);
//cout << "lasti:" << buffer << endl;
//
//itoa(station[i], buffer, 2);
//cout << "stati:" << buffer << endl;
//
//itoa(state | last[i], buffer, 2);
//cout << "left :" << buffer << endl;
//
//itoa(((ONE << vNum) - 1), buffer, 2);
//cout << "right:" << buffer << endl;
//cout << endl;

		if ((state | last[i]) != ((ONE << vNum) - 1))
		{
			return false;
		}
		if ((state | station[i]) == state)
		{
			continue;
		}
		if (DFS(vNum, i + 1, state | station[i], need, step + 1))
		{
			return true;
		}
	}
	return false;
}



