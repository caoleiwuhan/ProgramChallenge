#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstring>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_


// 能处理的最大数
const int MAX_NUM = 3010;

// 暂存数组
int arr[MAX_NUM];

// 当前处理数据大小
int numCount;

// 保存数据
int map[MAX_NUM];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	处理数组，判断是不是Jolly Jumper
*/
bool IsJollyJumper();

/*
	判断set中的数是否从1到Num
*/
bool IsFromOneToNum();

int main()
{

//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/110201.inp";
//
//	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
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
	// 1.读取输入数据，放到vector中
	char ch;
	while (cin.peek() != EOF)
	{
		// 数组中数据个数
		cin >> numCount;
		
		// 暂存数
		int num;
		for (int i = 0; i < numCount; ++i)
		{
			cin >> num;
			arr[i] = num;
		}
		// 处理数组数据
		bool ans = IsJollyJumper();
		if (ans)
		{
			cout << "Jolly" << endl;
		}
		else
		{
			cout << "Not jolly" << endl;
		}

		// 出去行尾的'\n'
		cin.get();
	}
}

bool IsJollyJumper()
{ // 相邻之差的绝对值...
	// 绝对值的最大
	int count = numCount - 1;
	if (count <= 0)
	{
		return true;
	}

	// 初始化map
	memset(map, 0, sizeof(map));
	
	for (int i = 0; i < count; ++i)
	{
		int num = abs(arr[i] - arr[i + 1]);
		// 从1开始
		map[num]++;
	}
	// 判断是否从1到count
	return IsFromOneToNum();
}

bool IsFromOneToNum()
{	
	for (int i = 1; i < numCount; ++i)
	{
		// 如果找不到i
		if (map[i] != 1)
		{
			return false;
		}
	}
	return true;
}