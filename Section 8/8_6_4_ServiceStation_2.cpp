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

// 第i个station能到达的地方
long long station[36];
// 第i个之后所有的都不能到达的
long long last[36];


//char buffer[65];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

/*
	回溯
	vNum:总点数
	cur：当前从哪一个开始
	state：当前状态
	need：需要的点数
	step：进行到第step个点数
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
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
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
		// 首先设置自己到自己可达：第1个就将左移0位
		for (int i = 0; i < vNum; ++i)
		{

//itoa(ONE << i, buffer, 2);
//cout << buffer << endl;

			station[i + 1] |= (ONE << i);
		}
		for (int i = 0; i < lNum; ++i)
		{
			cin >> v1 >> v2;
			// 设置v1与v2之间可达
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

		// 这里的i表示个数
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
	// 满足条件
	if (state == ((ONE << vNum) - 1))
	{
		return true;
	}

	// 如果搜完也没有结果
	if (step == need)
	{
		return false;
	}
	
	for (int i = cur; i <= vNum; ++i)
	{
		// 如果后面所有的都是station也不能满足条件，则直接剪枝跳过


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



