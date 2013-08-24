#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>
#include <hash_map>


using namespace std;

#define _MY_DEBUG_

const int MAXL = 1001;

int s[MAXL][MAXL];

int cut[51];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

void DP(int len, int num);

/*
	二分法查找
		找不到返回-1；
		找到返回索引
*/
int BinarySearch(int size, int length);

void TestBinarySearch();

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
	//TestBinarySearch();
			
}
void Process()
{
	int len = 0;
	int num = 0;
	int tmp = 0;
	while (cin >> len)
	{
		if (len == 0)
		{
			break;
		}
		cin >> num;
		for (int i = 0; i < num; ++i)
		{
			cin >> cut[i];
		}
		cut[num++] = 0;
		cut[num++] = len;

		sort(cut, cut + num);
		DP(len, num);
		cout << "The minimum cutting is " << s[0][len] << '.' << endl;
	}

}

void DP(int len, int num)
{
	memset(s, 0, sizeof(s));
	// 初始化切点
	//s[0][cut[0]] = 0;
	//for (int i = 0; i < num - 1; ++i)
	//{
	//	// s[cut[i]][cut[i+1]]
	//	s[cut[i]][cut[i+1]] = 0;
	//}
	//s[cut[num-1]][len] = 0;

	// s[i][j]:长度从i到j

	// 长度从1到len：（i，j）:i、j都应该是切点位置
	for (int l = 1; l <= len; ++l)
	{
		for (int i = 0; i <= len; ++i)
		{
			if (BinarySearch(num, i) == -1)
			{
				continue;
			}
			int j = i + l;
			// 保证i、j所在的位置都是切点
			if (BinarySearch(num, j) == -1)
			{
				continue;
			}
			int res = 0x7FFFFFFF;
			for (int k = i + 1; k < j; ++k)
			{
				if (BinarySearch(num, k) != -1)
				{					
					int tmp = s[i][k] + s[k][j] + l;
					if (tmp < res)
					{
						res = tmp;
					}						
				}				
			}
			if (res != 0x7FFFFFFF)
			{
				s[i][j] = res;
			}
		}
	}
}

int BinarySearch(int size, int length)
{
	int left = 0;
	int right = size;
	
	while (left <= right)
	{
		int middle = left + (right - left) / 2;
		if (cut[middle] == length)
		{
			return middle;
		}
		if (cut[middle] > length)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}
	return -1;
}

void TestBinarySearch()
{
	int num = 4;
	cut[0] = 25;
	cut[1] = 50;
	cut[2] = 75;
	cut[3] = 85;
	cout << BinarySearch(4, 25) << endl;
	cout << BinarySearch(4, 50) << endl;
	cout << BinarySearch(4, 75) << endl;
	cout << BinarySearch(4, 85) << endl;

	cout << BinarySearch(4, 2) << endl;
	cout << BinarySearch(4, 90) << endl;
	cout << BinarySearch(4, 55) << endl;
}