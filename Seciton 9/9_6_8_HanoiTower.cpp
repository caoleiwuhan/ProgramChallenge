//#include <iostream>
//#include <cstdlib>
//#include <vector>
//#include <map>
//#include <string>
//#include <cstring>
//#include <fstream>
//#include <cassert>
//#include <cmath>
//#include <iomanip>
//#include <algorithm>
//#include <sstream>
//#include <queue>
//#include <hash_map>
//
//
//using namespace std;
//
//#define _MY_DEBUG_
//
//const int MAXV = 60;
//
//// 每一个柱子上的数
//int towers[MAXV];
//
//// 柱子总数
//int nTower = 0;
//
//// 结果
//int ans = 0;
//
//
//
///*
//	MainStructure: 主结构
//*/
//void MainStructure();
//
///*
//	Process
//*/
//void Process();
//
///*
//	curNum:当前正在处理的数
//	curTower:当前已经使用的柱子数
//*/
//void dfs(int curNum, int curTower);
//
///*
//	判断是否结束：
//		柱子已经用完，且不能满足要求
//*/
//bool IsFinished(int curNum, int curTower);
//
///*
//	判断一个数是否是完全平方
//*/	
//bool IsNumSqrt(int num);
//
//
//int main()
//{
//	MainStructure();
//	return 0;
//}
//
//
//void MainStructure()
//{
//	
//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
//	//string inputStr = "D:/2挑战编程/input/110205.inp";
//	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
//	ifstream fin;
//	fin.open(inputStr);		
//
//	cin.rdbuf(fin.rdbuf());	
//
//	/*
//	ofstream fout;
//	fout.open(outputStr.c_str());
//	cout.rdbuf(fout.rdbuf());
//	*/
//
//#endif
//
//	Process();
//			
//}
//void Process()
//{
//	int count = 0;
//	cin >> count;
//	while (count--)
//	{
//		cin >> nTower;
//		memset(towers, 0, sizeof(towers));
//		ans = 0;
//		dfs(1, 0);
//		cout << ans << endl;
//	}
//}
//
//void dfs(int curNum, int curTower)
//{
//	if (IsFinished(curNum, curTower))
//	{
//		// 当前情况下，最好的结果就是tmp
//		int tmp = curNum - 1;
//		if (tmp > ans)
//		{
//			ans = tmp;
//		}
//		return;
//	}
//	// 选取
//	for (int i = 0; i < curTower; ++i)
//	{
//		int curTmp = towers[i];
//		if (IsNumSqrt(curTmp + curNum))
//		{
//			towers[i] = curNum;
//			dfs(curNum + 1, curTower);
//			towers[i] = curTmp;
//		}		
//	}
//	// 将数放到一个新的tower上
//	if (curTower < nTower)
//	{
//		towers[curTower] = curNum;
//		dfs(curNum + 1, curTower + 1);
//	}
//}
//
//bool IsFinished(int curNum, int curTower)
//{
//	if (curTower < nTower)
//	{
//		return false;
//	}
//	for (int i = 0; i < curTower; ++i)
//	{
//		if (IsNumSqrt(towers[i] + curNum))
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//bool IsNumSqrt(int num)
//{
//	int s = sqrt(double(num));
//	if (s * s == num)
//	{
//		return true;
//	}
//	return false;
//}

#include<cstdio>

int main()
{
	int n,t;
	scanf("%d",&t);
	for(int i=1;i<=t;++i)
	{
		scanf("%d",&n);
		if(n==1)
		printf("1\n");
		else
		{
			int sum=1,temp=2;
			for(int j=2;j<=n;++j)
			{
				if(j%2==1)
				temp+=2;
				sum+=temp;
			}
			printf("%d\n",sum);
		}
	}
	return 0;
}


